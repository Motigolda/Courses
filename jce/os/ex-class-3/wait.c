#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main( void ){
    pid_t pid = fork();
    if(pid == 0){
        pid_t pid_son = fork();
        if (pid_son == 0)
            printf("I am son 2, my pid is %d\n", getpid());
        else if(pid_son > 0)
        {
            wait(NULL);
            printf("I am son 1, my pid is %d\n", getpid());
        }
        else
            perror("Can\'t create son 2.\n");
    } 
    else if (pid > 0){
        wait(NULL);
        printf("I am the parent, my pid is %d\n", getpid());
    }
        
    else 
        perror("Can\'t create son 1.\n");
    
    return 0;
}