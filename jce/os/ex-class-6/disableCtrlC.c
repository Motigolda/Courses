#include <stdio.h>
#include <signal.h>

void sig_int_handler(int signum){
    printf("I don\'t want to quit!\n");
}

int main(void){
    signal(SIGINT, sig_int_handler);
    printf("infinite loop\n");
    while(1);
    return 0;
}

