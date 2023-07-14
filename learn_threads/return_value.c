#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void *roll_dice()
{
	int *result = malloc(sizeof(int));
	*result = (rand() % 6) + 1;
	printf("Thread result: %p\n", result);
	return ((void*) result);
}

int main()
{
	int *res;
	srand(time(NULL));
	pthread_t th;
	if (pthread_create(&th, NULL, &roll_dice, NULL))
		return 1;
	if (pthread_join(th, (void **) &res))
		return 2;
	printf("Main res: %p\n", res);
	printf("Result: %d\n", *res);
	free(res);
	return 0;
}
