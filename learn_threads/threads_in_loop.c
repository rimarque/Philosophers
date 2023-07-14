#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


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
	/*pthread_t t1;
	pthread_t t2;
	pthread_t t3;
	pthread_t t4;*/
	pthread_t th[4];
	int mails = 0;
	int i = 0;

	//iniciar o mutex antes de criar a thread
	pthread_mutex_init(&mutex, NULL); //alloca memoria
	//<adress to that mutex> <atributos>
	while(i < 4)
	{
		/*if(pthread_create(&th[i], NULL, &routine, &mails)) //se retornar != 0, erro
			return(i + 1);*/
		if(pthread_create(th + i, NULL, &routine, &mails)) //se retornar != 0, erro
			return(i + 1);
		printf("Thread %d has started\n", i);
		i++;
	}
	i = 0;
	while(i < 4)
	{
		/*if(pthread_join(th[i], NULL))
			return(3);*/
		if(pthread_join(*(th + i), NULL))
			return(3);
		printf("Thread %d has finished\n", i);
		i++;
	}
	//como esperar pelo child process, esperar que a thread acabe;
	pthread_mutex_destroy(&mutex); //destroy a memoria do mutex
	printf("number of mails: %d\n", mails);
	return(0);
}
