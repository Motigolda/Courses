#include <stdio.h>
#include <unistd.h>

int main( void ){
    pid_t pid = fork();
    if(pid == 0){
        // son 1
        pid_t pid_son = fork();
        if (pid_son == 0)
            printf("I am son 2, my pid is %d\n", pid_son);
        else if(pid_son > 0)
            printf("I am son 1, my pid is %d\n", pid_son);
        else
            perror("Can\'t create son 2.\n");
    } 
    else if (pid > 0)
        printf("I am the parent, my pid is %d\n", pid);
    else 
        perror("Can\'t create son 1.\n");
    
    return 0;
}