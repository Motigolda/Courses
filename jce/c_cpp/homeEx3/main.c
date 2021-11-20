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

#define COLOR_RED       "\033[0;31m"
#define COLOR_YELLOW    "\033[0;33m"
#define COLOR_WHITE     "\033[0;37m"
#define COLOR_DEFAULT   COLOR_WHITE

#define COMMANDS_LIST    "Welcome, what do you want to do?\n\
1. Print candidates.\n\
2. Print workers.\n\
3. Insert new Candidate.\n\
4. Hire candidate.\n\
5. Exit\n"

#define COMMAND_WAITING_SIGN "> "
#define STRINGS_EQUALS 0

#define ASCII_OFFSET_CHAR_TO_DIGIT 48
#define ASCII_OFFSET_UPPERCASE_TO_LOWERCASE 32


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
    ERROR_CADNIDATE_EXIST,
    ERROR_EMPLOYEE_EXIST
} error_code_t;

#define MSG_CANDIDATE_NOT_EXIST         "The candidate does\'nt exists.\n"
#define MSG_CANDIDATE_NOT_EXIST_FORMAT  "The candidate %s %s does\'nt exists.\n"
#define MSG_EMPLOYEE_NOT_EXIST          "The employee does\'nt exists.\n"
#define MSG_EMPLOYEE_NOT_EXIST_FORMAT   "The employee %s %s does\'nt exists.\n"
#define MSG_MAX_EMPLOYEES               "The employees table is full.\n"
#define MSG_MAX_CANDIDATES              "The candidates table is full.\n"
#define MSG_UNKNOWN_COMMAND             "Unknown command.\n"
#define MSG_UNKNOWN_COMMAND_FORMAT      "Unknown command: %s\n"
#define MSG_NO_EMPLOYEES                "No employees in the company.\n"
#define MSG_NO_CANDIDATES               "No candidates in the company.\n"
#define MSG_CANDIDATE_EXIST             "The candidate does exists.\n"
#define MSG_CANDIDATE_EXIST_FORMAT      "The candidate %s %s does exists.\n"
#define MSG_EMPLOYEE_EXIST              "The employee does exists.\n"
#define MSG_EMPLOYEE_EXIST_FORMAT       "The employee %s %s does exists.\n"        
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

// - DATA Layer: starts with DB, stands for DataBase
// - no logic, only duplicates and data existance checks
error_code_t DBAddCandidate(Developer candidate);
error_code_t DBDeleteCandidate(Developer candidate);
error_code_t DBAddEmployee(Developer employee);
error_code_t DBDeleteEmployee(Developer employee);
int DBGetCandidateKey(char* first_name, char* last_name); 
int DBGetEmployeeKey(char* first_name, char* last_name);
bool_t DBEmployeesTableFull();
bool_t DBCandidatesTableFull();
bool_t DBEmployeesTableEmpty();
bool_t DBCandidatesTableEmpty();
// privates
int _DBHash(Developer* _developer);

// Memory clean
void MemoryCleanExit();
void _MemoryCleanCandidateRecommenders(Developer* candidate);

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
    
}

void _ControllerCommandHireCandidate(){

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

#pragma endregion // Controller

#pragma region Controller_Commands

#pragma enregion // Controller Commands

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

    // TODO: insert new candidate flow
}

error_code_t HRHireCandidate(char* first_name, char* last_name){
    if (DBEmployeesTableFull())
        return ERROR_MAX_EMPLOYEES;

    // TODO: hire candidate flow
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

#pragma endregion // HR API

#pragma region DB
error_code_t DBAddCandidate(Developer candidate){

}

error_code_t DBDeleteCandidate(Developer candidate){

}

error_code_t DBAddEmployee(Developer employee){

}

error_code_t DBDeleteEmployee(Developer employee){

}

int DBGetCandidateKey(char* first_name, char* last_name){

} 

int DBEmployeeExists(char* first_name, char* last_name){

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
    char last_name_first_char_lowercased  = _CharToLowercase(_developer->last_name[1]);
    return (first_name_first_char_lowercased + last_name_first_char_lowercased) % MAX_ENTRYS_IN_TABLE;
}
char _CharToLowercase(const char to_lower){
    if (to_lower >= 'A' && to_lower <= 'Z')
        return to_lower + ASCII_OFFSET_UPPERCASE_TO_LOWERCASE;

    return to_lower;
}
#pragma endregion // DB

#pragma region Memory_clean
void MemoryCleanExit(){
    int i = 0;
    for (i = 0; i < MAX_ENTRYS_IN_TABLE; i++){
        int j = 0;
        _MemoryCleanCandidateRecommenders(candidates[i]);
    }  
}
void _MemoryCleanCandidateRecommenders(Developer* candidate){
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