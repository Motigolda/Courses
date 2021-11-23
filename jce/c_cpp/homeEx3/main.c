#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------- Constants and defines -------
#define TRUE    1
#define FALSE   0 

#define ANSWER_YES TRUE
#define ANSWER_NO FALSE
#define YES_SIGN "y"
#define MAX_COMPANY_RECOMMENDERS 2
#define MAX_EXTERNAL_RECOMMENDERS 2

#define N 20 // strings length.

#define STRING_LENGTH N // WRAPPER FOR N: string length
#define MAX_ENTRYS_IN_TABLE N // WRAPPER FOR N: entrys in array

#define COLOR_RED       "\033[0;31m"
#define COLOR_YELLOW    "\033[0;33m"
#define COLOR_WHITE     "\033[0;37m"
#define COLOR_DEFAULT   COLOR_WHITE

#define COMMANDS_LIST    "Welcome, what do you want to do?\n\
1. Print candidates.\n\
2. Print workers.\n\
3. Insert new Candidate.\n\
4. Hire candidate.\n\
5. Exit\n\
other - help\n"

#define COMMAND_WAITING_SIGN "> "
#define STRINGS_EQUALS 0

#define ASCII_OFFSET_CHAR_TO_DIGIT 48
#define ASCII_OFFSET_UPPERCASE_TO_LOWERCASE 32


// ------- Structs & Types -------
typedef int bool_t;
typedef bool_t yes_no_answer_t;

typedef struct recommender {
	char first_name[STRING_LENGTH];
    char last_name[STRING_LENGTH];
    char email[STRING_LENGTH];
} Recommender; 

typedef struct developer {
	char first_name[STRING_LENGTH];
    char last_name[STRING_LENGTH];
    char degree[STRING_LENGTH];
    struct developer*      company_recommenders[MAX_COMPANY_RECOMMENDERS];
    Recommender*    external_recommenders[MAX_EXTERNAL_RECOMMENDERS]; 
} Developer;

// type for command code. 
typedef enum command_code_t{
    CMD_INVALID,                // 0 for invalid command
    CMD_PRINT_CANDIDATES,       
    CMD_PRINT_EMPLOYEES,        
    CMD_INSERT_NEW_CANDIDATE,   
    CMD_HIRE_CANDIDATE,         
    CMD_EXIT,
    _CMD_COUNT                        
} command_code_t;

#define COMMANDS_COUNT          _CMD_COUNT - 1
#define COMMANDS_FIRST_NUMBER   CMD_INVALID+1
#define COMMANDS_LAST_NUMBER    _CMD_COUNT-1

// type for error codes
typedef enum error_code_t{
    SUCCESS,
    ERROR_CANDIDATE_NOT_EXIST   = -55,
    ERROR_EMPLOYEE_NOT_EXIST,
    ERROR_MAX_EMPLOYEES,
    ERROR_MAX_CANDIDATES,
    ERROR_UNKNOWN_COMMAND,
    ERROR_CANDIDATE_EXIST,
    ERROR_EMPLOYEE_EXIST,
    ERROR_NULL_POINTER,
    ERROR_UNKNOWN
} error_code_t;

#define MSG_CANDIDATE_NOT_EXIST         "The candidate does\'nt exists.\n"
#define MSG_CANDIDATE_NOT_EXIST_FORMAT  "The candidate %s %s does\'nt exists.\n"
#define MSG_EMPLOYEE_NOT_EXIST          "The employee does\'nt exists.\n"
#define MSG_EMPLOYEE_NOT_EXIST_FORMAT   "The employee %s %s does\'nt exists.\n"
#define MSG_MAX_EMPLOYEES               "Our company is fully hired!\n"
#define MSG_MAX_CANDIDATES              "There are no more place for a new candidates.\n"
#define MSG_UNKNOWN_COMMAND             "Unknown command.\n"
#define MSG_UNKNOWN_COMMAND_FORMAT      "Unknown command: %s\n"
#define MSG_NO_EMPLOYEES                "No employees in the company.\n"
#define MSG_NO_CANDIDATES               "No candidates in the company.\n"
#define MSG_CANDIDATE_EXIST             "The candidate does exists.\n"
#define MSG_CANDIDATE_EXIST_FORMAT      "The candidate %s %s does exists.\n"
#define MSG_EMPLOYEE_EXIST              "The employee does exists.\n"
#define MSG_EMPLOYEE_EXIST_FORMAT       "The employee %s %s does exists.\n"
#define MSG_CANDIDATE_ADD_SUCCESS       "Candidate added successfully.\n"
#define MSG_CANDIDATE_ADD_SUCCESS_FORMAT "The candidate %s %s added successfully.\n"    
#define MSG_UNKNOWN_ERROR               "Unknown Error\n"    
#define MSG_NULL_POINTER                "Null pointer error.\n"
#define MSG_CANDIDATE_HIRED             "The candidate is hired and now he is an employee.\n"
#define MSG_CANDIDATE_HIRED_FORMAT      "The candidate %s %s is hired and now he is an employee.\n"
#define MSG_EXIT                        "-----------------------------------------------\n\
Thanks for using HR Software By Moti Goldstein.\n\
-----------------------------------------------\n"

typedef char* color_t;

// globals 
static int current_num_of_employees     = 0; // max: MAX_ENTRYS_IN_TABLE
static int current_num_of_candidates    = 0; // max: MAX_ENTRYS_IN_TABLE
Developer *employees[MAX_ENTRYS_IN_TABLE], *candidates[MAX_ENTRYS_IN_TABLE]; 

// ------- MVC style components -------

// View component: get & show data

// starts with: UI
// functionallity:
void UIShowCommandList();
void UIShowCandidates(Developer *candidates[]);
void UIShowEmployees(Developer *employees[]);
void UIWaitForCommand(char* command);
void UIGetNewCandidateWithoutRecommenders(Developer *new_candidate);
void UIGetCandidateToHire(Developer *candidate_to_hire);
void UIGetCompanyRecommender(Developer* employee);
void UIGetExternalRecommender(Recommender* recommender);
yes_no_answer_t UIYesNoInput(char* question);

// messages and error reporting
void UIShowMessage(char* message);
void UIShowError(error_code_t error_code, char* error_message);
void UIShowWarning(error_code_t warning_code, char* warning_message);
void UIUnknownCommand(char* command);

// private funcs UI
void _UIPrintCandidate(Developer* candidate);
void _UIPrintEmployee(Developer* employee);
void _UIWrapStringToLength(char* string, const int length);
void _UIGetInput(char* destination, const int length);
void _UISetOutputColor(const color_t color);
// Controller Component: call UI and API functions, and make the main() logic.

// Run the ui loop and call to the right functions 
// starts with: Controller
// functionallity:
void ControllerMainLoop();
void ControllerRunCommand(command_code_t command_code);

// Commands from controller

void _ControllerCommandPrintCandidates();
void _ControllerCommandPrintEmployees();
void _ControllerCommandInsertNewCandidate();
void _ControllerCommandHireCandidate();
void _ControllerCommandExit();

// privates:

command_code_t _ControllerRawCommandToCommandCode(char* raw_command);
char _CharToDigit(const char to_digit);
char _CharToLowercase(const char to_lower);
void _StrToLower(char* str);
void _StrFormatWithFirstAndLastNames(char* destination, char* format, Developer* dev);
// Model Component: API for HR software

// - Business logic implemented here 
// - API Layer: starts with HR
// - functionallity:
Developer** HRGetCandidates();
Developer** HRGetEmployees();
error_code_t HRInsertNewCandidate(Developer candidate);
error_code_t HRHireCandidate(char* first_name, char* last_name);
bool_t HRAreThereCandidates();
bool_t HRAreThereEmployees();
bool_t HRISCandidatesDBFull();
bool_t HRISEmployeesDBFull();
bool_t HRIsCandidateExist(Developer *candidate);
bool_t HRIsEmployeeExist(Developer *employee);
// - DATA Layer: starts with DB, stands for DataBase
// - no logic, only duplicates and data existance checks
error_code_t DBAddCandidate(Developer candidate);
error_code_t DBDeleteCandidate(Developer candidate);
error_code_t DBAddEmployee(Developer employee);
int DBGetCandidateKey(char* first_name, char* last_name); 
int DBGetEmployeeKey(char* first_name, char* last_name);
bool_t DBEmployeesTableFull();
bool_t DBCandidatesTableFull();
bool_t DBEmployeesTableEmpty();
bool_t DBCandidatesTableEmpty();
bool_t DBEmployeeExists(char* first_name, char* last_name);
bool_t DBCandidateExists(char* first_name, char* last_name);
// privates
int _DBHash(Developer* _developer);
void _DBRemoveCompanyRecommenders(Developer* candidate);
void _DBLowerAllData(Developer* dev);
// Memory clean
void MemoryCleanExit();
void _MemoryCleanCandidateRecommenders(Developer* candidate);
void _MemoryCleanCandidateCompanyRecommenders(Developer* candidate);

//
// ------- main program -------
//
int main(){
    ControllerMainLoop();

    MemoryCleanExit();
    return 0;
}
//
// ----------------------------
//
#pragma region UI

void UIShowCommandList(){
    printf(COMMANDS_LIST);
}

void UIShowCandidates(Developer *candidates[]){
    printf("---- Showing Candidates ----\n");
    int i = 0;
    int candidates_counter = 0;
    for (i = 0; i < MAX_ENTRYS_IN_TABLE; i++){
        if(candidates[i] != NULL){
            _UIPrintCandidate(candidates[i]);
            candidates_counter++;
        }
    }
    if (candidates_counter == 1)
        printf("--- There is %d candidate ---\n", candidates_counter);
    else
        printf("--- There are %d candidates ---\n", candidates_counter);
    printf("--- End of candidates ----\n\n");
}

void UIShowEmployees(Developer *employees[]){
    printf("---- Showing Employees ----\n");
    int i = 0;
    int employees_counter = 0;
    for (i = 0; i < MAX_ENTRYS_IN_TABLE; i++){
        if(employees[i] != NULL){
            _UIPrintEmployee(employees[i]);
            employees_counter++;
        }
            
    }
    if (employees_counter == 1)
        printf("--- There is %d employee ---\n", employees_counter);
    else
        printf("--- There are %d employees ---\n", employees_counter);
    printf("---- End of employees ----\n\n");
}

void UIWaitForCommand(char* command){
    printf(COMMAND_WAITING_SIGN);
    scanf("%s", command);
    *(command + 2) = 0;
}

void UIGetCandidateToHire(Developer *candidate_to_hire){
    if ( candidate_to_hire == NULL) return;
    printf("Enter candidate\'s data: \n");
    printf("First name: ");
    _UIGetInput(candidate_to_hire->first_name, STRING_LENGTH);
    printf("Last name: ");
    _UIGetInput(candidate_to_hire->last_name, STRING_LENGTH);
}
// messages and error reporting
void UIShowMessage(char* message){
    _UISetOutputColor(COLOR_DEFAULT);
    printf("%s", message);
}

void UIShowError(error_code_t error_code, char* error_message){
    _UISetOutputColor(COLOR_RED);
    printf("Error[0x%x]: %s\n", error_code, error_message);
    _UISetOutputColor(COLOR_WHITE);
}

void UIShowWarning(error_code_t warning_code, char* warning_message){
    _UISetOutputColor(COLOR_YELLOW);
    printf("Warning[0x%x]: %s\n", warning_code, warning_message);
    _UISetOutputColor(COLOR_DEFAULT);
}

void UIUnknownCommand(char* command){
    char* full_unknown_command_string = (char*)malloc(sizeof(char)*(strlen(MSG_UNKNOWN_COMMAND_FORMAT) + strlen(command)));
    sprintf(full_unknown_command_string, MSG_UNKNOWN_COMMAND_FORMAT, command);
    UIShowWarning(ERROR_UNKNOWN_COMMAND, full_unknown_command_string);
    free(full_unknown_command_string);
    UIShowCommandList();
}

void UIGetNewCandidateWithoutRecommenders(Developer *new_candidate){
    if (new_candidate == NULL) return;

    printf("Enter new candidate information:\n");
    printf("First name: ");
    _UIGetInput(new_candidate->first_name, STRING_LENGTH);
    printf("Last name: ");
    _UIGetInput(new_candidate->last_name, STRING_LENGTH);
    printf("Degree: ");
    _UIGetInput(new_candidate->degree, STRING_LENGTH);
}

void UIGetCompanyRecommender(Developer* employee){
    if (employee == NULL) return;
    printf("Enter company recommender information:\n");
    printf("First name: ");
    _UIGetInput(employee->first_name, STRING_LENGTH);
    printf("Last name: ");
    _UIGetInput(employee->last_name, STRING_LENGTH);
}

void UIGetExternalRecommender(Recommender* recommender){
    if (recommender == NULL) return;

    printf("Enter external recommender information:\n");
    printf("First name: ");
    _UIGetInput(recommender->first_name, STRING_LENGTH);
    printf("Last name: ");
    _UIGetInput(recommender->last_name, STRING_LENGTH);
    printf("Email: ");
    _UIGetInput(recommender->email, STRING_LENGTH);
}

yes_no_answer_t UIYesNoInput(char* question){
    if (question == NULL)
        printf("Yes no question: ");
    else
        printf("%s", question);

    printf(" [%s for yes, other for no]: ", YES_SIGN);
    char* raw_answer = (char*)malloc(sizeof(char)*3);
    _UIGetInput(raw_answer, 3);
    yes_no_answer_t answer = ANSWER_NO;
    if (strcmp(raw_answer, YES_SIGN) == STRINGS_EQUALS)
        answer = ANSWER_YES;

    free(raw_answer);
    raw_answer = NULL;
    return answer;
}

// privates
void _UIPrintCandidate(Developer* candidate){
    if (candidate == NULL) return;

    printf("## Candidate: \n%s %s, Degree: %s\n",  candidate->first_name, 
                candidate->last_name,
                candidate->degree);

    int i = 0;
    for(i = 0; i < MAX_COMPANY_RECOMMENDERS; i++){
        if(candidate->company_recommenders[i] != NULL)
            printf("Employee recommender %d: %s %s\n", i+1, 
            candidate->company_recommenders[i]->first_name,
            candidate->company_recommenders[i]->last_name);
    }

    for(i = 0; i < MAX_EXTERNAL_RECOMMENDERS; i++){
        if(candidate->external_recommenders[i] != NULL)
            printf("External recommender %d: %s %s, Email: %s\n", i+1, 
            candidate->external_recommenders[i]->first_name,
            candidate->external_recommenders[i]->last_name,
            candidate->external_recommenders[i]->email);               
    }
}

void _UIPrintEmployee(Developer* employee){
    if (employee == NULL) return;

    printf("## Employee: \n%s %s, Degree: %s\n",  employee->first_name, 
                employee->last_name,
                employee->degree);
}

void _UIWrapStringToLength(char* string, const int length){
    if (string == NULL) return;

    *(string + length - 1) = 0;
}

void _UIGetInput(char* destination, const int length){
    char buffer[length];
    scanf("%s", buffer);
    _UIWrapStringToLength(buffer, length);
    strcpy(destination, buffer);
}

void _UISetOutputColor(const color_t color){
    printf("%s", color);
}

#pragma endregion // UI

#pragma region Controller

void ControllerMainLoop(){
    UIShowCommandList();
    char* current_raw_command = (char*)malloc(sizeof(char) * 3);
    command_code_t current_command = CMD_INVALID;

    do{
        UIWaitForCommand(current_raw_command);
        current_command = _ControllerRawCommandToCommandCode(current_raw_command);
        if (current_command == CMD_INVALID)
            UIUnknownCommand(current_raw_command);
        else
            ControllerRunCommand(current_command);
    } while(current_command != CMD_EXIT);

    free(current_raw_command);
}

void ControllerRunCommand(command_code_t command_code){
    switch (command_code)
    {
    case CMD_PRINT_CANDIDATES:
        _ControllerCommandPrintCandidates();
        break;
    
    case CMD_PRINT_EMPLOYEES:
        _ControllerCommandPrintEmployees();
        break;
    
    case CMD_INSERT_NEW_CANDIDATE:
        _ControllerCommandInsertNewCandidate();
        break;

    case CMD_HIRE_CANDIDATE:
        _ControllerCommandHireCandidate();
        break;

    case CMD_EXIT:
        _ControllerCommandExit();
        break;
    
    default:
        UIShowError(ERROR_UNKNOWN_COMMAND, "Unknown command catched after input validation.");
    }
}

// privates 

void _ControllerCommandPrintCandidates(){
    if(HRAreThereCandidates())
        UIShowCandidates(HRGetCandidates());
    else
        UIShowMessage(MSG_NO_CANDIDATES);
}

void _ControllerCommandPrintEmployees(){
    if(HRAreThereEmployees())
        UIShowEmployees(HRGetEmployees());
    else
        UIShowMessage(MSG_NO_EMPLOYEES);
}

void _ControllerCommandInsertNewCandidate(){
    if(HRISCandidatesDBFull()){
        UIShowWarning(ERROR_MAX_CANDIDATES, MSG_MAX_CANDIDATES);
    }
    else{
        Developer candidate = { 0 };      
        UIGetNewCandidateWithoutRecommenders(&candidate);
        
        if (HRIsCandidateExist(&candidate)){
            char* candidate_exist_message = (char*)malloc(strlen(MSG_CANDIDATE_EXIST_FORMAT) + strlen(candidate.first_name) + strlen(candidate.last_name));
            sprintf(candidate_exist_message, MSG_CANDIDATE_EXIST_FORMAT, candidate.first_name, candidate.last_name);
            UIShowError(ERROR_CANDIDATE_EXIST, candidate_exist_message);
            free(candidate_exist_message);
            return;
        }

        error_code_t err = ERROR_UNKNOWN;
        yes_no_answer_t insert_recommenders = UIYesNoInput("Do you want to enter recommenders?");
        if (insert_recommenders == ANSWER_YES){
            int i = 0;
            yes_no_answer_t have_external_recommenders = UIYesNoInput("Do you want to enter external recommender?");
            yes_no_answer_t have_another_one = ANSWER_YES;
            if(have_external_recommenders){
                for(i = 0; i < MAX_EXTERNAL_RECOMMENDERS; i++){
                    if (!have_another_one) break;
                    Recommender recommender = { 0 };
                    UIGetExternalRecommender(&recommender);
                    candidate.external_recommenders[i] = &recommender;
                    if (i + 1 < MAX_EXTERNAL_RECOMMENDERS)
                        have_another_one = UIYesNoInput("Do you have another one? ");
                }
            }
            yes_no_answer_t have_company_recommenders = UIYesNoInput("Do you want to enter company recommender?");
            if (have_company_recommenders){
                have_another_one = ANSWER_YES;
                i = 0;
                while(i < MAX_EXTERNAL_RECOMMENDERS){
                    if (!have_another_one) break;
                    Developer employee = { 0 };
                    UIGetCompanyRecommender(&employee);
                    if (!HRIsEmployeeExist(&employee)){
                        UIShowError(ERROR_EMPLOYEE_NOT_EXIST, MSG_EMPLOYEE_NOT_EXIST);
                    }
                    else {
                        candidate.company_recommenders[i] = &employee;
                        i++;
                    }
                    if (i < MAX_EXTERNAL_RECOMMENDERS)
                        have_another_one = UIYesNoInput("Do you have another one? ");
                }
            }
                


        }
        else{
        
        }
        err = HRInsertNewCandidate(candidate);
        
        switch (err)
        {
            case SUCCESS:
            {
                char* success_message = (char*)malloc(strlen(MSG_CANDIDATE_ADD_SUCCESS_FORMAT) + strlen(candidate.first_name) + strlen(candidate.last_name));
                sprintf(success_message, MSG_CANDIDATE_ADD_SUCCESS_FORMAT, candidate.first_name, candidate.last_name);
                UIShowMessage(success_message);
                free(success_message);
                break;
            }
            case ERROR_MAX_CANDIDATES:
                UIShowError(ERROR_MAX_CANDIDATES, MSG_MAX_CANDIDATES);
                break;
            case ERROR_CANDIDATE_EXIST:
            {
                char* candidate_exist_message = (char*)malloc(strlen(MSG_CANDIDATE_EXIST_FORMAT) + strlen(candidate.first_name) + strlen(candidate.last_name));
                sprintf(candidate_exist_message, MSG_CANDIDATE_EXIST_FORMAT, candidate.first_name, candidate.last_name);
                UIShowError(ERROR_CANDIDATE_EXIST, candidate_exist_message);
                free(candidate_exist_message);
                break;                
            }

            default:
                UIShowError(err, MSG_UNKNOWN_ERROR);
                break;
        }  
    }
}

void _ControllerCommandHireCandidate(){
    if(HRISEmployeesDBFull())
        UIShowWarning(ERROR_MAX_EMPLOYEES, MSG_MAX_EMPLOYEES);
    else {
        Developer candidate_to_hire = { 0 };
        UIGetCandidateToHire(&candidate_to_hire);
        error_code_t err = HRHireCandidate(candidate_to_hire.first_name, candidate_to_hire.last_name);
        switch (err)
        {
        case SUCCESS:{
            UIShowMessage(MSG_CANDIDATE_HIRED);
            break;
        }
        case ERROR_MAX_EMPLOYEES:{
            UIShowError(err, MSG_MAX_EMPLOYEES);
            break;
        }
        
        default:
            UIShowError(err, MSG_UNKNOWN_ERROR);
            break;
        }
    }
}

void _ControllerCommandExit(){
    UIShowMessage(MSG_EXIT);
}

command_code_t _ControllerRawCommandToCommandCode(char* raw_command){
    if(raw_command == NULL || strlen(raw_command) != 1)
        return CMD_INVALID;

    char digit_value = _CharToDigit(*(raw_command));
    if (digit_value < COMMANDS_FIRST_NUMBER || digit_value > COMMANDS_LAST_NUMBER)
        return CMD_INVALID;

    return (command_code_t)digit_value;
}

char _CharToDigit(const char to_digit){
    return to_digit - ASCII_OFFSET_CHAR_TO_DIGIT;
}

void _StrToLower(char* str){
    if (str == NULL) return;

    int current_char = 0;
    while(*(str + current_char) != 0){
        *(str + current_char) = _CharToLowercase(*(str + current_char));
        current_char++;
    }
}

#pragma endregion // Controller

#pragma region Controller_Commands

#pragma endregion // Controller Commands

#pragma region HR_API

Developer** HRGetCandidates(){
    return candidates;
}

Developer** HRGetEmployees(){
    return employees;
}

error_code_t HRInsertNewCandidate(Developer candidate){
    if (DBCandidatesTableFull())
        return ERROR_MAX_CANDIDATES;

    if (DBCandidateExists(candidate.first_name, candidate.last_name))
        return ERROR_CANDIDATE_EXIST;

    return DBAddCandidate(candidate);
}

error_code_t HRHireCandidate(char* first_name, char* last_name){
    if (DBEmployeesTableFull())
        return ERROR_MAX_EMPLOYEES;

    if (DBEmployeeExists(first_name, last_name))
        return ERROR_EMPLOYEE_EXIST;

    Developer candidate = { 0 };
    strcpy(candidate.first_name, first_name);
    strcpy(candidate.last_name, last_name);
    int err = DBAddEmployee(candidate);
    if (err != 0)
        return err;

    return DBDeleteCandidate(candidate);
}

bool_t HRAreThereCandidates(){
    return !DBCandidatesTableEmpty();
}

bool_t HRAreThereEmployees(){
    return !DBEmployeesTableEmpty();
}

bool_t HRISCandidatesDBFull(){
    return DBCandidatesTableFull();
}

bool_t HRISEmployeesDBFull(){
    return DBEmployeesTableFull();
}

bool_t HRIsCandidateExist(Developer *candidate){
    if (candidate == NULL) return FALSE;

    return DBCandidateExists(candidate->first_name, candidate->last_name);
}

bool_t HRIsEmployeeExist(Developer *employee){
    if (employee == NULL) return FALSE;

    return DBEmployeeExists(employee->first_name, employee->last_name);
}

#pragma endregion // HR API

#pragma region DB

error_code_t DBAddCandidate(Developer candidate){
    if (DBCandidateExists(candidate.first_name, candidate.last_name))
        return ERROR_CANDIDATE_EXIST;

    int candidate_hash = _DBHash(&candidate);
    _DBLowerAllData(&candidate);
    int tries_count = 0;
    while(tries_count < MAX_ENTRYS_IN_TABLE){
        if (candidates[candidate_hash] == NULL){
            candidates[candidate_hash] = (Developer*)malloc(sizeof(Developer));
            strcpy(candidates[candidate_hash]->first_name, candidate.first_name);
            strcpy(candidates[candidate_hash]->last_name, candidate.last_name);
            strcpy(candidates[candidate_hash]->degree, candidate.degree);
            int i = 0;
            for (i = 0; i < MAX_EXTERNAL_RECOMMENDERS; i++){
                if (candidate.external_recommenders[i] != NULL){
                    Recommender* current_reco = (Recommender*)malloc(sizeof(Recommender));
                    memcpy(current_reco, candidate.external_recommenders[i], sizeof(Recommender));
                    candidates[candidate_hash]->external_recommenders[i] = current_reco;
                } 
                else
                    candidates[candidate_hash]->external_recommenders[i] = NULL;
            }
            for (i = 0; i < MAX_COMPANY_RECOMMENDERS; i++){
                if (candidate.company_recommenders[i] != NULL){
                    int employee_recommender_key = DBGetEmployeeKey(candidate.company_recommenders[i]->first_name, candidate.company_recommenders[i]->last_name);
                    candidates[candidate_hash]->company_recommenders[i] = employees[employee_recommender_key];
                }   
                else
                    candidates[candidate_hash]->company_recommenders[i] = NULL;
            }
            break;
        }
        else{
            tries_count++;
            candidate_hash++;
            candidate_hash %= MAX_ENTRYS_IN_TABLE;
        }
    }
    if (tries_count == MAX_ENTRYS_IN_TABLE)
        return ERROR_MAX_CANDIDATES;
    return SUCCESS;
}

error_code_t DBDeleteCandidate(Developer candidate){
    if (!DBCandidateExists(candidate.first_name, candidate.last_name))
        return ERROR_CANDIDATE_NOT_EXIST;
    
    int candidate_key = DBGetCandidateKey(candidate.first_name, candidate.last_name);
    _MemoryCleanCandidateRecommenders(candidates[candidate_key]);
    free(candidates[candidate_key]);
    candidates[candidate_key] = NULL;
    return SUCCESS;
}

error_code_t DBAddEmployee(Developer candidate){
    if (DBEmployeesTableFull())
        return ERROR_MAX_EMPLOYEES;
    
    if (DBEmployeeExists(candidate.first_name, candidate.last_name))
        return ERROR_EMPLOYEE_EXIST;

    if (!DBCandidateExists(candidate.first_name, candidate.last_name))
        return ERROR_CANDIDATE_NOT_EXIST;
        
    _DBLowerAllData(&candidate);
    int candidate_key = DBGetCandidateKey(candidate.first_name, candidate.last_name);
    int employee_hash = _DBHash(&candidate);
    int i = 0;
    while(i < MAX_ENTRYS_IN_TABLE){
        if (employees[employee_hash] == NULL){
            employees[employee_hash] = (Developer*)malloc(sizeof(Developer));
            strcpy(employees[employee_hash]->first_name, candidates[candidate_key]->first_name);
            strcpy(employees[employee_hash]->last_name, candidates[candidate_key]->last_name);
            strcpy(employees[employee_hash]->degree, candidates[candidate_key]->degree);
            return SUCCESS;
        } 
        else {
            i++;
            employee_hash++;
            employee_hash %= MAX_ENTRYS_IN_TABLE;
        }
    }
    return ERROR_MAX_EMPLOYEES;   
}

int DBGetCandidateKey(char* first_name, char* last_name){
    if (first_name == NULL || last_name == NULL) 
        return ERROR_NULL_POINTER;
    
    _StrToLower(first_name);
    _StrToLower(last_name);
    Developer dev = { 0 };
    strcpy(dev.first_name, first_name);
    strcpy(dev.last_name, last_name);
    int i = 0;
    int candidate_hash  = _DBHash(&dev);
    while(i < MAX_ENTRYS_IN_TABLE){
        if (candidates[candidate_hash] != NULL){
            bool_t first_name_equals = strcmp(first_name, candidates[candidate_hash]->first_name) == STRINGS_EQUALS;
            bool_t last_name_equals  = strcmp(last_name, candidates[candidate_hash]->last_name) == STRINGS_EQUALS;
            if (first_name_equals && last_name_equals)
                return candidate_hash;
        } 
        i++;
        candidate_hash++;
        candidate_hash %= MAX_ENTRYS_IN_TABLE;
    }
    return ERROR_CANDIDATE_NOT_EXIST;
} 

int DBGetEmployeeKey(char* first_name, char* last_name){
    if (first_name == NULL || last_name == NULL) 
        return ERROR_NULL_POINTER;
    
    _StrToLower(first_name);
    _StrToLower(last_name);
    Developer dev = { 0 };
    strcpy(dev.first_name, first_name);
    strcpy(dev.last_name, last_name);
    int i = 0;
    int employee_hash  = _DBHash(&dev);
    while(i < MAX_ENTRYS_IN_TABLE){
        if(employees[employee_hash] != NULL){
            bool_t first_name_equals = strcmp(first_name, employees[employee_hash]->first_name) == STRINGS_EQUALS;
            bool_t last_name_equals  = strcmp(last_name, employees[employee_hash]->last_name) == STRINGS_EQUALS;
            if (first_name_equals && last_name_equals)
                return employee_hash;
        }

        i++;
        employee_hash++;
        employee_hash %= MAX_ENTRYS_IN_TABLE;
    }
    return ERROR_EMPLOYEE_NOT_EXIST;    
}

bool_t DBEmployeeExists(char* first_name, char* last_name){
    return DBGetEmployeeKey(first_name, last_name) != ERROR_EMPLOYEE_NOT_EXIST;
}

bool_t DBCandidateExists(char* first_name, char* last_name){
    return DBGetCandidateKey(first_name, last_name) != ERROR_CANDIDATE_NOT_EXIST;
}

bool_t DBEmployeesTableFull(){
    int i = 0; 
    for(i = 0; i < MAX_ENTRYS_IN_TABLE; i++)
        if (employees[i] == NULL)
            return FALSE;

    return TRUE;
}

bool_t DBCandidatesTableFull(){
    int i = 0; 
    for(i = 0; i < MAX_ENTRYS_IN_TABLE; i++)
        if (candidates[i] == NULL)
            return FALSE;

    return TRUE;
}

bool_t DBEmployeesTableEmpty(){
    int i = 0; 
    for(i = 0; i < MAX_ENTRYS_IN_TABLE; i++)
        if (employees[i] != NULL)
            return FALSE;

    return TRUE;
}

bool_t DBCandidatesTableEmpty(){
    int i = 0; 
    for(i = 0; i < MAX_ENTRYS_IN_TABLE; i++)
        if (candidates[i] != NULL)
            return FALSE;

    return TRUE;
}

// privates
int _DBHash(Developer* _developer){
    char first_name_first_char_lowercased = _CharToLowercase(_developer->first_name[0]);
    char last_name_first_char_lowercased  = _CharToLowercase(_developer->last_name[0]);
    unsigned char addition = first_name_first_char_lowercased + last_name_first_char_lowercased;
    return addition % MAX_ENTRYS_IN_TABLE;
}

void _DBRemoveCompanyRecommenders(Developer* candidate){
    if (candidate == NULL) return;

    int i = 0;
    for (i = 0; i < MAX_COMPANY_RECOMMENDERS; i++)
        if(candidate->company_recommenders[i] != NULL)
            candidate->company_recommenders[i] = NULL;
}
void _DBLowerAllData(Developer* dev){
    if (dev == NULL) return;

    _StrToLower(dev->first_name);
    _StrToLower(dev->last_name);
    _StrToLower(dev->degree);

    int i = 0;

    for (i = 0; i < MAX_EXTERNAL_RECOMMENDERS; i++){
        if (dev->external_recommenders[i] != NULL){
            _StrToLower(dev->external_recommenders[i]->first_name);
            _StrToLower(dev->external_recommenders[i]->last_name);
            _StrToLower(dev->external_recommenders[i]->email);
        }
    }
}
char _CharToLowercase(const char to_lower){
    if (to_lower >= 'A' && to_lower <= 'Z')
        return to_lower + ASCII_OFFSET_UPPERCASE_TO_LOWERCASE;

    return to_lower;
}

void _StrFormatWithFirstAndLastNames(char* destination, char* format, Developer* dev){
    if (destination == NULL ||
        format == NULL ||
        dev == NULL) return;

    sprintf(destination, format, dev->first_name, dev->last_name);
}
#pragma endregion // DB

#pragma region Memory_clean

void MemoryCleanExit(){
    int i = 0;
    for (i = 0; i < MAX_ENTRYS_IN_TABLE; i++){
        _MemoryCleanCandidateRecommenders(candidates[i]);
        free(candidates[i]);
        free(employees[i]);
        candidates[i] = NULL;
        employees[i] = NULL;
    }  
}

void _MemoryCleanCandidateRecommenders(Developer* candidate){
    if (candidate == NULL) return;
    
    int i = 0;
    for(int i = 0; i < MAX_EXTERNAL_RECOMMENDERS; i++){
        if(candidate->external_recommenders[i] != NULL){
            free(candidate->external_recommenders[i]);
            candidate->external_recommenders[i] = NULL;
        }
    } 
}

void _MemoryCleanCandidateCompanyRecommenders(Developer* candidate){
      if (candidate == NULL) return;
    
    int i = 0;
    for(int i = 0; i < MAX_COMPANY_RECOMMENDERS; i++){
        if(candidate->company_recommenders[i] != NULL){
            free(candidate->company_recommenders[i]);
            candidate->company_recommenders[i] = NULL;
        }
    }   
}

#pragma endregion