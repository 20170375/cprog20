#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>
#include<string.h>

int main(int argc, char* argv[])
{
	int pid = fork();

	if(!pid){
		printf("I'm child\n");

		char* args[] = {"/bin/ls", "-al", (char*)0};
		char* env_args[] = {(char*)0};

		if(execve(args[0], args, env_args) < 0){
			printf("%s: Command not found.\n",args[0]);
			exit(1);
		}

	} else {
		printf("I'm parent\n");
		int status;
		wait(&status);
	}

	return 0;
}
