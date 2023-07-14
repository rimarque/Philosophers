#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;

void *print_nbr(void *nbr)
{
	pthread_mutex_lock(&mutex);
	printf("%d\n", (*(int *)nbr));
	pthread_mutex_unlock(&mutex);
}

int main()
{
	pthread_t th[10];

	int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
	int i = 0;
	pthread_mutex_init(&mutex, NULL);
	while(i < 10)
	{
		int *a = malloc(sizeof(int));
		*a = primes[i];
		if(pthread_create(th + i, NULL, &print_nbr, a))
			return(1);
		i++;
	}
	/*while(i < 10)
	{
		if(pthread_create(th + i, NULL, &print_nbr, (void *)&primes[i]))
			return(1);
		i++;
	}*/
	i = 0;
	while(i < 10)
	{
		pthread_join(*(th + i), NULL);
		i++;
	}
	return(0);
}
