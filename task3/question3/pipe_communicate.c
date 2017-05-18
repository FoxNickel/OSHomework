#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>

int main()
{
	int mutex[2],p1,p2,p3;
	char in[110],out[110];
	pipe(mutex);
	while((p1=fork())==-1);
	if(!p1){
		lockf(mutex[1],1,0);
		sprintf(in,"child 1 is send message!");
		write(mutex[1],in,50);
		sleep(1);
		lockf(mutex[1],0,0);
		exit(0);
	}else{
		while((p2=fork())==-1);
		if(!p2){
			lockf(mutex[1],1,0);
			sprintf(in,"child 2 is send message!");
			write(mutex[1],in,50);
			sleep(1);
			lockf(mutex[1],0,0);
			exit(0);
		}else{
			while((p3=fork())==-1);
			if(!p3){
				lockf(mutex[1],1,0);
				sprintf(in,"child 3 is send message!");
				write(mutex[1],in,50);
				sleep(1);
				lockf(mutex[1],0,0);
				exit(0);
			}else{
				wait(0);
				read(mutex[0],out,50);
				printf("%s\n",out);
				wait(0);
				read(mutex[0],out,50);
				printf("%s\n", out);
				wait(0);
				read(mutex[0],out,50);
				printf("%s\n", out);
				exit(0);
			}
		}
	}
	return 0;
}