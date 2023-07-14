#include "sum_numbers.h"

pthread_mutex_t mutex;

void *sum_nbr(void *nbr)
{
	t_primes *p_n;
	int *sum;
	p_n = (t_primes *)nbr;
	pthread_mutex_unlock(&mutex);
	printf("%d", p_n->index);
	int i  = p_n->index;
	*sum = 0;
	while (i < p_n->index + 5)
	{
		*sum += p_n->array[i];
		printf("sum_in_loop: %d\n", *sum);
		i++;
	}
	printf("sum_function: %d\n", *sum);
	pthread_mutex_unlock(&mutex);
	return((void *)sum);
}

int main()
{
	pthread_t	th[2];
	t_primes	p_n;
	int	*result_a;
	int *result_b;
	int sum = 0;
	p_n.flag = 1;

	int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
	p_n.array = malloc(sizeof(int) * 10);
	int i = 0;
	while(i < 10)
	{
		p_n.array[i] = primes[i];
		i++;
	}
	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while(i < 2)
	{
		printf("oi 3\n");
		if(i == 0)
			p_n.index = 0;
		else
		{
		 	sleep(1);
		 	p_n.index = 5;
		}
		if(pthread_create(&th[i], NULL, &sum_nbr, (void *)&p_n))
			return(1);
		i++;
		printf("oi 4\n");
	}
	pthread_join(th[0], (void **)&result_a);
	printf("%d\n", *result_a);
	sum += *result_a;
	pthread_join(th[1], (void **)&result_b);
	printf("%d\n", *result_b);
	sum += *result_b;
	printf("sum: %d\n", sum);
	return(0);
}
