#include <stdio.h>
#include <stdlib.h>
#include <errno.h> 
#include <signal.h>

int main (void){

void sigint_handler(int sig);
void sigtstp_handler(int sig);
void sigquit_handler(int sig);
char s[200];

if (signal(SIGINT,sigint_handler)==SIG_ERR){
	perror("signal");
	exit(1);
}

if (signal(SIGTSTP,sigtstp_handler)==SIG_ERR){
        perror("signal");
        exit(1);
}

if (signal(SIGQUIT,sigquit_handler)==SIG_ERR){
        perror("signal");
        exit(1);
}

printf("Enter a string:\n");

if (fgets(s,200,stdin)==NULL)
	perror("gets");
else
	printf("you entered: %s\n", s);

return 0;
}

void sigint_handler(int sig){
	printf("This is a special signal handler for INT\n");
}

void sigtstp_handler(int sig){
        printf("This is a special signal handler for TSTP\n");
}

void sigquit_handler(int sig){
        printf("This is a special signal handler for SIGQUIT\n");
}
