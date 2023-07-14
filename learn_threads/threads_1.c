#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *routine()
{
	printf("Test from threads\n");
	sleep(3);
	printf("Ending thread\n");
}

int main(int argc, char **argv)
{
	pthread_t t1, t2; //place to store information abaut the thread

	if(pthread_create(&t1, NULL, &routine, NULL) != 0)
		return(1); //erro
		 //<ponteiro para a trhead a inicializar>
		//<atributos>; <ponteiro para a funcao que se executa quando a trhead e criada>;
		//<argumento a passar a funcao>;
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return(1);
	pthread_join(t1, NULL); //e o wait das threads <tread>; <ponteiro que guarda o resultado da thread>
	pthread_join(t1, NULL);
	return(0);
}
