#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ------- Constants and defines -------
#define TRUE    1
#define FALSE   0 

#define MAX_COMPANY_RECOMMENDERS 2
#define MAX_EXTERN_RECOMMENDERS 2

#define N 20 // strings length.

#define STRING_LENGTH N // WRAPPER FOR N: string length
#define MAX_ENTRYS_IN_TABLE N // WRAPPER FOR N: entrys in array

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
    struct Developer*      company_recommenders[MAX_COMPANY_RECOMMENDERS];
    Recommender*    externals_recommenders[MAX_EXTERN_RECOMMENDERS]; 
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
void UIShowCandidates(Developer *candidates[], const int num_of_candidates);
void UIShowEmployees(Developer *employees[], const int num_of_employees);
Developer UIGetNewCandidate();
Developer UIGetCandidateToHire();
// messages and error reporting
void UIShowMessage(char* message);
void UIShowError(error_code_t error_code, char* error_message);
void UIShowWarning(error_code_t warning_code, char* warning_message);

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

int main(){
    return 0;
}