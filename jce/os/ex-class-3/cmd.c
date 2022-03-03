#include <stdio.h>
#include <unistd.h>

int main ( void ){
    char* firstCommand[] = {"ls", "-l", NULL};
    char* secondCommand[] = {"pwd", NULL};
    pid_t pid = fork();

    if (pid == 0)
        execvp(firstCommand[0], firstCommand);
    else if (pid > 0)
        execvp(secondCommand[0], secondCommand);
    else
        perror("Can\'t create a new process.");

    return 0;
}