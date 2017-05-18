#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
	int pipefd[2];
	int pid;
	char buff[100];

	if(pipe(pipefd) == -1){
		printf("Create pipe failed\n");
		exit(1);
	}

	pid = fork();
	if(pid==-1){
		printf("fork failed\n");
		exit(1);
	}

	if(pid==0){
		printf("I am chlid,my pid is %d\n",pid);
		if(read(pipefd[0],buff,100)<0){
			printf("write error\n");
		}

		printf("%s\n",buff);

		bzero(buff,100);

		snprintf(buff,100,"Message from child");
		if(write(pipefd[1],buff,strlen(buff))<0){
			printf("write error\n");
			exit(1);
		}
	}else{
		printf("I am parent,my pid is %d\n",pid);

		snprintf(buff,100,"Message from parent");
		if(write(pipefd[1],buff,strlen(buff))<0){
			printf("write error\n");
			exit(1);
		}

		sleep(1);

		bzero(buff,100);

		if(read(pipefd[0],buff,100)<0){
			printf("write error\n");
		}

		printf("%s\n",buff);

		wait(NULL);
	}
	return 0;
}