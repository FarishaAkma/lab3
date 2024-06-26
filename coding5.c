#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PIN_LENGTH 4
#define PIN_WAIT_INTERVAL 2

void getPIN (char pin[PIN_LENGTH + 1]){
	
	srand(getpid() + getppid());
	pin[0] = 49 + rand() % 7;

	for (int i=1;i<PIN_LENGTH;i++){
		pin[i] = 48 + rand() % 7;
	}
	
	pin[PIN_LENGTH] = '\0';
}

int main (void){
	
	while (1){
		int pipefds[2];
		char pin[PIN_LENGTH+1];
		char buffer[PIN_LENGTH+1];

		pipe(pipefds);
		pid_t pid = fork();

		if (pid == 0){
			getPIN(pin);
			close(pipefds[0]);
			write(pipefds[1],pin,PIN_LENGTH+1);

			printf("Generating PIN in child and sending to parent...\n");

			sleep(PIN_WAIT_INTERVAL);

			exit(EXIT_SUCCESS);
		}

		if (pid>0){
			wait(NULL);

			close(pipefds[1]);
			read(pipefds[0],buffer,PIN_LENGTH+1);
			close(pipefds[0]);
			printf("Parent received PIN '%s' from child.\n\n", buffer);
		}
	}
	
	return EXIT_SUCCESS;
}
