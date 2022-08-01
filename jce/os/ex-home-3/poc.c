#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>

typedef struct _process_t{
    char args[256][256];
    int fd_redirect_input_to_here;
    int fd_redirect_output_to_here;
    bool run_bg;
    bool run_nohup;
} process_t;

void PipeFlow(){
        char *args1[] = {
        "ls",
        "-l",
        NULL
    };
    
    char *args2[] = {
        "grep",
        "poc",
        NULL
    };
    
    int pipe_fd[2] = { 0 };
    bool pipe_creation_failed = pipe(pipe_fd) == -1;
    if(pipe_creation_failed){
        perror("Cant open pipe");
        exit(EXIT_FAILURE);
    }

    pid_t check_pid = fork();

    bool in_son = check_pid == 0;
    bool in_parent = check_pid > 0;
    bool error_detected = check_pid < 0;
    
    if (in_parent){
        // here we will run args1
        dup2(pipe_fd[1], STDOUT_FILENO);
        execvp(args1[0], args1);
    }
    if (in_son){
        // here we will run args2
        dup2(pipe_fd[0], STDIN_FILENO);
        execvp(args2[0], args2);
    }
    if (error_detected){
        perror("Cant fork.");
        exit(1);
    }
}
void handler(int signo){
    if(signo == SIGHUP)
        printf("hup\n");
}

int main(void){
    char *args[] = {
        "sleep",
        "666",
        NULL
    };

    pid_t check_me = fork();

    if(check_me == 0){
        signal(SIGHUP, handler);
        FILE *fd = fopen("nohup.txt", "w");
        dup2(fileno(fd), STDOUT_FILENO);
        execvp(args[0], args);
    }
    
    return 0;
}