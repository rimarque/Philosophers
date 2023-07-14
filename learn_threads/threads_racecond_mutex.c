#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

//ideia de mutex com a variavel lock
/*int lock = 0;

void	*routine(void *mails)
{
	int i = 0;
	while (i++ < 100)
	{
	if(lock == 1)
		//wait until the lock is 0;
	lock = 1;
	(*(int *)mails)++;
	lock = 0;
	//read the value of mails
	//increment the value
	//write the value of mails in memory
	}
	return(NULL);
}*/

//MUTEX
pthread_mutex_t mutex;

void	*routine(void *mails)
{
	int i = 0;
	while (i++ < 1000000)
	{
		pthread_mutex_lock(&mutex);
		(*(int *)mails)++;
		pthread_mutex_unlock(&mutex);
		//read the value of mails
		//increment the value
		//write the value of mails in memory
	}
	return(NULL);
}

int main(int argc, char* argv[])
{
	pthread_t t1;
	pthread_t t2;
	int mails = 0;

	//iniciar o mutex antes de criar a thread
	pthread_mutex_init(&mutex, NULL); //alloca memoria
	//<adress to that mutex> <atributos>
	if(pthread_create(&t1, NULL, &routine, &mails)) //se retornar = 0, erro
		return(1);
	if(pthread_create(&t2, NULL, &routine, &mails)) //se retornar = 0, erro
		return(2);
	if(pthread_join(t1, NULL))
		return(3);
	if(pthread_join(t2, NULL))
		return(4);
	//como esperar pelo child process, esperar que a thread acabe;
	pthread_mutex_destroy(&mutex); //destroy a memoria do mutex
	printf("number of mails: %d\n", mails);
	return(0);
}
