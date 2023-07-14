#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

//as threads partilham
void *routine(void *x)
{
	(*(int *)x)++;
	sleep(10);
	printf("Value of x 1: %d\n", *(int *)x);
	//printf("Process id %d\n", getpid());
}

void *routine2(void *x)
{
	//sleep(2);
	printf("Value of x 2: %d\n", *(int *)x);
}

int main(int argc, char* argv[])
{
	pthread_t t1;
	pthread_t t2;
	int x = 0;

	if(pthread_create(&t1, NULL, &routine, &x)) //se retornar != 0, erro
		return(1);
	if(pthread_create(&t2, NULL, &routine2, &x)) //se retornar != 0, erro
		return(2);
	if(pthread_join(t1, NULL))
		return(3);
	if(pthread_join(t2, NULL))
		return(4);
	//como esperar pelo child process, esperar que a trhead acabe;
	return(0);
}
