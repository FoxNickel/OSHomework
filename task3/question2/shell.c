#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CMD_LEN 100//max length of cmd you typed
#define CMD_NUM 4//max num of cmd

/*
	judge whether cmd is valid
	@params cmd-cmd to be judged
	@return 0:cmd is valid;-1:cmd is invalid
*/
int isValidCmd(char* cmd){
	char *VALID_CMD[CMD_NUM] = {"cmd1","cmd2","cmd3","exit"};
	int i=0;
	for(i=0;i<CMD_NUM;i++){
		if(strcmp(cmd,VALID_CMD[i])==0){
			return 0;
		}
	}
	return -1;
}

int main()
{
	char command[MAX_CMD_LEN];
	/*infinite loop to run program*/
	while(1){
		printf("please input command:");
		scanf("%s",command);
		/*cmd is valid,go ahead*/
		if(isValidCmd(command)==0){
			/*if cmd is exit,exit the program*/
			if(strcmp(command,"exit")==0){
				exit(0);
			}else{
				/*if cmd is mot exit,fork a process to run cmd*/
				pid_t pid;
				pid = fork();
				/*fork fail*/
				if(pid<0){
					printf("Fork fail");
				}
				/*if in child process,run cmd*/
				else if(pid==0){
					printf("Son is running\n");
					if(strcmp(command,"exit")==0){
						exit(0);
					}else if(strcmp(command,"cmd1")==0){
						execl("./cmd1","cmd1",NULL);
					}else if(strcmp(command,"cmd2")==0){
						execl("./cmd2","cmd2",NULL);
					}
					else if(strcmp(command,"cmd3")==0){
						execl("./cmd3","cmd3",NULL);
					}
				}else{
					/*if in father process,wait child process to finish task*/
					wait(0);
				}
			}
		}else{
			/*cmd is invalid,re-enter a cmd*/
			printf("Invalid Command\n");
		}
	}
	return 0;
}