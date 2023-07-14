#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
	int x = 2;
	int pid = fork();
	if (pid == -1)
		return(1);
	if (pid == 0)
		x++;
	//sleep(2);
	printf("Value of x: %d\n", x);
	//printf("Processes id %d\n", getpid());
	if(pid != 0) //main process
		wait(NULL); //wait for child process
	return(0);
}
