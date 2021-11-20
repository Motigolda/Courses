#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ------- Constants and defines -------
#define TRUE    1
#define FALSE   0 

#define MAX_COMPANY_RECOMMENDERS 2
#define MAX_EXTERNAL_RECOMMENDERS 2

#define N 20 // strings length.

#define STRING_LENGTH N // WRAPPER FOR N: string length
#define MAX_ENTRYS_IN_TABLE N // WRAPPER FOR N: entrys in array

#define COMMANDS_LIST    "Welcome, what do you want to do?\n\
1. Print candidates.\n\
2. Print workers.\n\
3. Insert new Candidate.\n\
4. Hire candidate.\n\
5. Exit\n"

#define COMMAND_WAITING_SIGN "> "
#define STRINGS_EQUALS 0
// ------- Structs & Types -------
typedef int bool_t;

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
typedef enum commad_code_t{
    CMD_INVALID,                // 0 for invalid command
    CMD_PRINT_CANDIDATES,       
    CMD_PRINT_EMPLOYEES,        
    CMD_INSERT_NEW_CANDIDATE,   
    CMD_HIRE_CANDIDATE,         
    CMD_EXIT                        
} command_code_t;

// type for error codes
typedef enum error_code_t{
    SUCCESS,
    ERROR_MAX_EMPLOYEES,
    ERROR_MAX_CANDIDATES,
    ERROR_CANDIDATE_NOT_EXIST,
    ERROR_EMPLOYEE_NOT_EXIST
} error_code_t;

const char *const error_descriptions[] = {
    [SUCCESS] =                     "success",
    [ERROR_MAX_EMPLOYEES]           = "No more place in employees table",
    [ERROR_MAX_CANDIDATES]          = "No more place in cadidates table", 
    [ERROR_CANDIDATE_NOT_EXIST]     = "Candidate not exists",
    [ERROR_EMPLOYEE_NOT_EXIST]      = "Employee not exists"
};

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
void UIGetNewCandidate(Developer *new_candidate, Developer company_recommenders[], Recommender external_recommenders[]);
void UIGetCandidateToHire(Developer *candidate_to_hire);
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
// Controller Component: call UI and API functions, and make the main() logic.

// Run the ui loop and call to the right functions 
// starts with: Controller
// functionallity:
void ControllerMainLoop();
void ControllerRunFunction(command_code_t command_code);

// Model Component: API for HR software

// - Business logic implemented here 
// - API Layer: starts with HR
// - functionallity:
Developer* HRGetCandidates();
Developer* HRGetEmployees();
error_code_t HRInsertNewCandidate(Developer candidate);
error_code_t HRHireCandidate(Developer candidate);

// - DATA Layer: starts with DB, stands for DataBase
// - no logic, only duplicates and data existance checks
error_code_t DBAddCandidate(Developer candidate);
error_code_t DBDeleteCandidate(Developer candidate);
error_code_t DBAddEmployee(Developer employee);
error_code_t DBDeleteEmployee(Developer employee);
bool_t DBCandidateExists(Developer candidate);
bool_t DBEmployeeExists(Developer employee);
bool_t DBEmployeesTableFull();
bool_t DBCandidatesTableFull();

// Memory clean
void MemoryCleanExit();
void MemoryCleanCandidateRecommenders(Developer* candidate);

//
// ------- main program -------
//
int main(){

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
    for (i = 0; i < MAX_ENTRYS_IN_TABLE; i++){
        if(candidates[i] != NULL)
            _UIPrintCandidate(candidates[i]);
    }
    printf("--- End of candidates ----\n");
}

void UIShowEmployees(Developer *employees[]){
    printf("---- Showing Employees ----\n");
    int i = 0;
    for (i = 0; i < MAX_ENTRYS_IN_TABLE; i++){
        if(employees[i] != NULL)
            _UIPrintEmployee(employees[i]);
    }
    printf("---- End of employees ----\n");
}

void UIWaitForCommand(char* command){
    printf(COMMAND_WAITING_SIGN);
    scanf("%s", command);
    *(command + 2) = 0;
}

void UIGetNewCandidate( Developer *new_candidate,    
                        Developer company_recommenders[MAX_COMPANY_RECOMMENDERS], 
                        Recommender external_recommenders[MAX_EXTERNAL_RECOMMENDERS]){
    if( new_candidate == NULL ) return;
    
    int i = 0;
    for (i = 0; i < MAX_COMPANY_RECOMMENDERS; i++)
        new_candidate->company_recommenders[i] = NULL;
    
    for (i = 0; i < MAX_EXTERNAL_RECOMMENDERS; i++)
        new_candidate->external_recommenders[i] = NULL;
        
    printf("Please enter candidate basic information:\n");
    
    printf("First name: ");
    _UIGetInput(new_candidate->first_name, STRING_LENGTH);

    printf("Last name: ");
    _UIGetInput(new_candidate->last_name, STRING_LENGTH);

    printf("Enter degree: ");
    _UIGetInput(new_candidate->degree, STRING_LENGTH);

    printf("Are there recommenders? [y for yes / other for no]: ");
    char* are_there_recommenders = (char*)malloc(sizeof(char)*3);
    _UIGetInput(are_there_recommenders, 3);

    if(strcmp(are_there_recommenders, "y") == STRINGS_EQUALS){
        for(i = 0; i < MAX_COMPANY_RECOMMENDERS; i++){
            char add_another_recommender[3];
            printf("Add company recommender? [y for yes / other for no]: ");
            _UIGetInput(add_another_recommender, 3);

            if (strcmp(add_another_recommender, "y") == STRINGS_EQUALS){
                printf("Enter first name: ");
                _UIGetInput(company_recommenders[i].first_name, STRING_LENGTH);
                printf("Enter last name: ");
                _UIGetInput(company_recommenders[i].last_name, STRING_LENGTH); 
            }
            else break;
        }
        for(i = 0; i < MAX_EXTERNAL_RECOMMENDERS; i++){
            char add_another_recommender[3];
            printf("Add external recommender? [y for yes / other for no]: ");
            _UIGetInput(add_another_recommender, 3);

            if (strcmp(add_another_recommender, "y") == STRINGS_EQUALS){

                printf("Enter first name: ");
                _UIGetInput(external_recommenders[i].first_name, STRING_LENGTH);
                printf("Enter last name: ");
                _UIGetInput(external_recommenders[i].last_name, STRING_LENGTH);
                printf("Enter email: ");
                _UIGetInput(external_recommenders[i].email, STRING_LENGTH);                            
            }
            else break;
        }
    }
    free(are_there_recommenders);
    are_there_recommenders = NULL;
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
void UIShowMessage(char* message);
void UIShowError(error_code_t error_code, char* error_message);
void UIShowWarning(error_code_t warning_code, char* warning_message);
void UIUnknownCommand(char* command);

// privates
void _UIPrintCandidate(Developer* candidate){
    if (candidate == NULL) return;

    printf("Candidate: %s %s, Degree: %s\n",  candidate->first_name, 
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

    printf("Employee: %s %s, Degree: %s\n",  employee->first_name, 
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

#pragma endregion // UI

#pragma region Controller

#pragma endregion // Controller

#pragma region HR_API

#pragma endregion // HR API

#pragma region DB

#pragma endregion // DB

#pragma region Memory_clean
void MemoryCleanExit(){
    int i = 0;
    for (i = 0; i < MAX_ENTRYS_IN_TABLE; i++){
        int j = 0;
        MemoryCleanCandidateRecommenders(candidates[i]);
    }  
}
void MemoryCleanCandidateRecommenders(Developer* candidate){
    if (candidate == NULL) return;
    
    int i = 0;
    for(int i = 0; i < MAX_EXTERNAL_RECOMMENDERS; i++){
        if(candidate->external_recommenders[i] != NULL){
            Recommender* temp_pointer = candidate->external_recommenders[i];
            candidate->external_recommenders[i] = NULL;
            free(candidate->external_recommenders[i]);
            candidate->external_recommenders[i] = NULL;
            temp_pointer = NULL;
        }
    } 
}
#pragma endregion