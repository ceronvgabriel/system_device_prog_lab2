/*
lab2 - GCeron
*/ 

#include <stdio.h>		
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h>


void catcher();
void catcher2();
int i = 1;
int finish;

//
//catcher
//
void catcher(){
printf("Sig_Catched");
if (i == 1){
	i=0;
	printf("Stoping");
	while(1);//halts the process, it will reenter the catcher after receiving the next signal
}
else{

	i=1;
}

}


void catcher2(){
printf("sig_Catched");
finish=1;
}



//
//Main
//
int main(){

int i, fp,n;
char * line = NULL;
size_t len = 0;
ssize_t read;
pid_t pid, ppid,ppid2;
int ret,ret2;

ppid = getpid();
signal(SIGUSR1,catcher);
signal(SIGUSR2,catcher2);


ret=fork();

if(ret==0){ //child
	printf("I'm child :D");
	ret2=fork();
	
	if(ret2==0){
		printf("I'm child 2");
		sleep(10);
		kill(ppid2,SIGUSR2);
		kill(ppid,SIGUSR2);
	} //child
	else{
		while(finish==0){
		printf("sleeping");
		n = rand()%4;
		sleep(n);
		kill(ppid,SIGUSR1);
		}
		printf("Sleeping end");
	}
}
else{
	//fp=fopen("list.txt", "r");
	printf("I'm parent");
	//while(finish==0);
	/*while (1){

		if((read = getline(&line, &len, fp)) != -1 ){
			//strtok(line, "\n");
			printf("%c\n",atoi(line));
		}
		else{
			rewind(fp);
		}

	}*/
	printf("printing end");
}

exit(0);
}
