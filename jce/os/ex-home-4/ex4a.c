#include <stdio.h>

#include <stdint.h>

#include <stdlib.h>

#include <stdbool.h>

#include <string.h>

#include <pthread.h>

#include <math.h>

#pragma region Typedefs
typedef enum _option_selector_t {
    OPT_UNKNOWN = 0,
        OPT_INVALID = 1,
        OPT_CALC_POLYNOMIAL,
        OPT_CLOSE,
        OPT_EMPTY_LINE
}
option_selector_t;

typedef struct _term_t {
    int32_t coefficient;
    int32_t exponent;
}
term_t;

typedef struct _polynomial_t {
    term_t ** terms; // ends with pointer to NULL  
}
polynomial_t;

typedef struct _task_t {
    option_selector_t selected_option;
    polynomial_t polynomial;
    int32_t solve_for;
}
task_t;

typedef enum _buffers_in_parse_t {
    BUFF_COEF,
    BUFF_EXP,
    BUFF_SOLVE_FOR
}
buffers_in_parse_t;

typedef struct _term_with_solve_for_and_result_t {
    term_t * term;
    int32_t solve_for;
}
term_with_solve_for_and_result_t;

#pragma endregion

#pragma region Macros

#define INPUT_LINE_MAX_LENGTH (512)
#define MAX_TERMS (256)

#define STR_WAIT_TO_USER_INPUT "P(x), x0 / done: "
#define STR_INVALID_INPUT "Invalid Input!"
#define STR_UNKNOWN_INPUT "Unknown Input!"
#define STR_VALUE_OF_CALC_FORMAT "P(%d) = %ld\n"
#define STR_CLOSE "done\n"

#define IS_DIGIT(ch)('0' <= (ch) && (ch) <= '9')
#define IS_PLUS(ch)((ch) == '+')
#define IS_MINUS(ch)((ch) == '-')
#define IS_COMMA(ch)((ch) == ',')
#define IS_SPACE(ch)((ch) == ' ')
#define IS_NEWLINE(ch)((ch) == '\n')
#define IS_CIRCUMFLEX(ch)((ch) == '^')
#define IS_X(ch)((ch) == 'x' || (ch) == 'X')

#define SET_INVALID_AND_BREAK(task) task -> selected_option = OPT_UNKNOWN;break;
// use these to describe variable as in/out
#define IN
#define OUT

#pragma endregion

#pragma region Type Functions Headers
void AddTermToPolynomial(polynomial_t * polynomial, term_t * term);

void CleanPolynomial(polynomial_t * polynomial);

void CleanTask(task_t * task);

#pragma endregion

#pragma region Component Functions Headers
void GetLineFromUser(OUT char * line_from_user);

task_t * ParseUserInput(char * line_from_user);

int64_t CalculatePolynomial(polynomial_t * polynomial, int32_t solve_for_x);

#pragma endregion
// Heres the functions who changes with the calucation method
#pragma region Calculation Functions Headers
int64_t CalculatePolynomialUsingThreads(polynomial_t * polynomial, int32_t solve_for);

int64_t CalculateTerm(term_t * term, int32_t solve_for);

void * CalculateTermUsingThread(void * term_with_solve_for);

#pragma endregion

#pragma region Handling Functions Headers
void MainLoop();

void HandleTask(task_t * task);
#pragma endregion

int main(void) {
    MainLoop();
    return 0;
}

#pragma region Type Functions Implementation
void AddTermToPolynomial(polynomial_t * polynomial, term_t * term) {
    if (polynomial -> terms == NULL) {
        polynomial -> terms = malloc(sizeof(term));
        polynomial -> terms[0] = NULL;
    }

    uint32_t i = 0;
    while (polynomial -> terms[i] != NULL)
        i++;

    polynomial -> terms = realloc(polynomial -> terms, (i + 2) * sizeof(term));
    polynomial -> terms[i] = malloc(sizeof(term_t));
    polynomial -> terms[i] -> coefficient = term -> coefficient;
    polynomial -> terms[i] -> exponent = term -> exponent;
    polynomial -> terms[i + 1] = NULL;
}

void CleanPolynomial(polynomial_t * polynomial) {
    if (polynomial == NULL)
        return;

    if (polynomial -> terms == NULL)
        return;

    uint32_t i = 0;
    while (polynomial -> terms[i] != NULL) {
        free(polynomial -> terms[i]);
        polynomial -> terms[i] = NULL;
        i++;
    }

    free(polynomial -> terms);
    polynomial -> terms = NULL;
}

void CleanTask(task_t * task) {
    if (task == NULL)
        return;

    CleanPolynomial( & task -> polynomial);
}
#pragma endregion

#pragma region Component Functions Implementation
void GetLineFromUser(OUT char * line_from_user) {
    if (line_from_user == NULL)
        return;

    memset(line_from_user, 0, INPUT_LINE_MAX_LENGTH);

    printf(STR_WAIT_TO_USER_INPUT);

    fgets(line_from_user, INPUT_LINE_MAX_LENGTH, stdin);

    line_from_user[INPUT_LINE_MAX_LENGTH - 1] = 0;
}

task_t * ParseUserInput(char * line_from_user) {
    if (line_from_user == NULL)
        return NULL;

    task_t * task = malloc(sizeof(task_t));

    memset(task, 0, sizeof(task_t));

    task -> selected_option = OPT_UNKNOWN;

    if (strcmp(line_from_user, STR_CLOSE) == 0)
        task -> selected_option = OPT_CLOSE;

    if (IS_NEWLINE(line_from_user[0]))
        task -> selected_option = OPT_EMPTY_LINE;

    if (task -> selected_option != OPT_UNKNOWN)
        return task;

    task -> selected_option = OPT_CALC_POLYNOMIAL;
    uint32_t i = 0;
    uint32_t buff_ind = 0;
    char buffer[INPUT_LINE_MAX_LENGTH] = {
        0
    };
    bool is_buffering = true;
    buffers_in_parse_t current_buffer = BUFF_COEF;
    char current_char = line_from_user[0];
    term_t current_term = {
        0
    };

    while (current_char != 0) {
        if (is_buffering) {
            if (IS_DIGIT(current_char)) {
                buffer[buff_ind] = current_char;
                ++buff_ind;
            } else if (IS_X(current_char)) {
                if (current_buffer == BUFF_COEF) {
                    if(strlen(buffer) == 0)
                        current_term.coefficient = 1;
                    else
                        current_term.coefficient = atoi(buffer);
                    memset(buffer, 0, INPUT_LINE_MAX_LENGTH);
                    buff_ind = 0;
                    current_buffer = BUFF_EXP;
                    is_buffering = false;
                } else {
                    SET_INVALID_AND_BREAK(task);
                }

            } else if (IS_PLUS(current_char)) {
                if (current_buffer == BUFF_EXP) {
                    current_term.exponent = atoi(buffer);
                    memset(buffer, 0, INPUT_LINE_MAX_LENGTH);
                    buff_ind = 0;
                    current_buffer = BUFF_COEF;
                    AddTermToPolynomial( & task -> polynomial, & current_term);
                    current_term.coefficient = 0;
                    current_term.exponent = 0;
                } else {
                    SET_INVALID_AND_BREAK(task);
                }

            } else if (IS_COMMA(current_char)) {
                if (current_buffer == BUFF_EXP) {
                    current_term.exponent = atoi(buffer);
                    memset(buffer, 0, INPUT_LINE_MAX_LENGTH);
                    buff_ind = 0;
                    AddTermToPolynomial( & task -> polynomial, & current_term);
                    current_term.coefficient = 0;
                    current_term.exponent = 0;
                    is_buffering = false;
                } else {
                    SET_INVALID_AND_BREAK(task);
                }

            } else if (IS_NEWLINE(current_char)) {
                if (current_buffer == BUFF_SOLVE_FOR) {
                    task -> solve_for = atoi(buffer);
                    break;
                } else {
                    SET_INVALID_AND_BREAK(task);
                }
            } else if (IS_CIRCUMFLEX(current_char)) {
                SET_INVALID_AND_BREAK(task);
            }
        } else {
            if (IS_SPACE(current_char)) {
                is_buffering = true;
                current_buffer = BUFF_SOLVE_FOR;
            } else if (IS_CIRCUMFLEX(current_char)) {
                is_buffering = true;
            } else {
                SET_INVALID_AND_BREAK(task);
            }
        }

        i++;
        current_char = line_from_user[i];
    }

    if (task -> selected_option == OPT_INVALID) {
        CleanPolynomial( & task -> polynomial);
    }
    return task;
}

int64_t CalculatePolynomial(polynomial_t * polynomial, int32_t solve_for) {
    if (polynomial == NULL)
        return 0;

    return CalculatePolynomialUsingThreads(polynomial, solve_for);
}

#pragma endregion

#pragma region Calculation Functions Implementations
int64_t CalculatePolynomialUsingThreads(polynomial_t * polynomial, int32_t solve_for) {

    int64_t result = 0;

    term_with_solve_for_and_result_t terms_for_thread[MAX_TERMS] = {
        0
    };
    pthread_t threads[MAX_TERMS] = {
        0
    };
    uint32_t current_term_pointer = 0;
    int32_t err = 0;

    while (polynomial -> terms[current_term_pointer] != NULL) {
        terms_for_thread[current_term_pointer].term = polynomial -> terms[current_term_pointer];
        terms_for_thread[current_term_pointer].solve_for = solve_for;
        err = pthread_create( &
            threads[current_term_pointer],
            NULL,
            CalculateTermUsingThread, &
            terms_for_thread[current_term_pointer]
        );

        if (err != 0) {
            printf("Failed to create a new thread.\n");
            exit(1);
        }

        ++current_term_pointer;
    }

    uint32_t num_of_threads = current_term_pointer;
    int64_t * current_result = NULL;

    for (int i = 0; i < num_of_threads; i++) {
        pthread_join(threads[i], (void ** ) & current_result);
        result += * current_result;
        free(current_result);
    }

    return result;
}

int64_t CalculateTerm(term_t * term, int32_t solve_for) {
    if (term == NULL)
        return 0;

    double coef = (double) term -> coefficient;
    double exp = (double) term -> exponent;

    int64_t result = (int64_t)(pow(solve_for, exp) * coef);
    return result;
}

void * CalculateTermUsingThread(void * term_with_solve_for) {
    if (term_with_solve_for == NULL)
        return NULL;

    term_with_solve_for_and_result_t * args = (term_with_solve_for_and_result_t * ) term_with_solve_for;

    term_t * term = args -> term;
    int32_t solve_for = args -> solve_for;

    int64_t * result = malloc(sizeof(int64_t));

    * result = CalculateTerm(term, solve_for);
    pthread_exit((void * ) result);
}

#pragma endregion

#pragma region Handling Functions Implementations
void MainLoop() {
    char line_buffer[INPUT_LINE_MAX_LENGTH] = {
        0
    };
    bool keep_running = true;
    task_t * task = NULL;
    while (keep_running) {
        memset(line_buffer, 0, INPUT_LINE_MAX_LENGTH);

        GetLineFromUser(line_buffer);

        task = ParseUserInput(line_buffer);

        HandleTask(task);

        if (task -> selected_option == OPT_CLOSE)
            keep_running = false;

        CleanTask(task);
        free(task);
        task = NULL;
    }
}

void HandleTask(task_t * task) {
    if (task == NULL)
        return;

    switch (task -> selected_option) {
    case OPT_CALC_POLYNOMIAL:
        printf(STR_VALUE_OF_CALC_FORMAT,
            task -> solve_for,
            CalculatePolynomial( & task -> polynomial, task -> solve_for));
        break;

    case OPT_EMPTY_LINE:
        break;

    case OPT_CLOSE:
        break;

    case OPT_INVALID:
        printf("%s\n", STR_INVALID_INPUT);
        break;

    case OPT_UNKNOWN:
    default:
        printf("%s\n", STR_UNKNOWN_INPUT);
        break;
    }
}
#pragma endregion
