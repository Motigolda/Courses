#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define IS_PARENT(pid) (0 < pid)
#define IS_SON(pid) (pid == 0)

bool son_can_run = false;
bool IsPrime(int n);

int GetRandomPrime();

int main(void){
    srand(time(NULL));
    pid_t fork_output_pid = -1;
    fork_output_pid = fork();
    int random_prime = 0;
    
    if (IS_PARENT(fork_output_pid)){
        pid_t son_pid = fork_output_pid;
        
        printf("Parent PID: %d\nSon PID: %d\n", 
            getpid(), son_pid);

        random_prime = GetRandomPrime();

        kill(son_pid, SIGKILL);

        printf("Prime found in parent process: %d\n", 
            random_prime);
    }
    else if (IS_SON(fork_output_pid)){
        random_prime = GetRandomPrime();

        kill(getppid(), SIGKILL);

        printf("Prime found in son process: %d\n", 
            random_prime);
    }
    else{
        perror("Cant create son process");
        exit(1);
    }
    return 0;
}

bool IsPrime(int n){
    if (n < 2) return false;

    for (int i = 2; i < (int)sqrt((double)n); i++)
        if (n % i == 0)
            return false;

    return true;
}

int GetRandomPrime(){
    int current_random_number = 0;
    while(1)
        if (IsPrime(current_random_number = rand() % 10000))
            return current_random_number;
}
