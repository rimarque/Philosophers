#include "philo.h"

void create_list(t_list *data)
{
	int count;
	t_node *new;

	count = 1;
	while(count <= data->n_philo)
	{
		new = create_node(data, count);
		insert_last(data, new);
		count++;
	}
}

void init_list(t_list *data, int argc, char **argv)
{
	data->n_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		data->n_eat = -1;
	if (argc == 6)
		data->n_eat = ft_atoi(argv[5]);
	data->index = 1;
	data->head = NULL;
	pthread_mutex_init(&data->mutex, NULL);
	create_list(data);
}

void	eating(t_node *philo)
{
	pthread_mutex_lock(&philo->fork.mutex);
	philo->fork.status = USING;
	printf("Philo %d as taken a fork", philo->index);
	philo->prev->fork.status = USING;
	printf("Philo %d as taken a fork", philo->prev->index);
	philo->status = EATING;
	printf("Philo %d is eating", philo->index);
	philo->fork.status = DROPED;
	printf("Philo %d as taken a fork", philo->index);
	philo->prev->fork.status = DROPED;
	printf("Philo %d as taken a fork", philo->prev->index);
	pthread_mutex_unlock(&philo->fork.mutex);
}
void	sleeping(t_node *philo)
{
	philo->status = EATING;
	printf("Philo %d is sleeping", philo->index);
}

void	thinking(t_node *philo)
{
	philo->status = THINKING;
	printf("Philo %d is thinking", philo->index);
}

void	*routine(void *data)
{
	t_node *philo;
	int count;

	pthread_mutex_lock(&((t_list *)data)->mutex);
	philo = ((t_list *)data)->head;
	count = 0;
	while(count < ((t_list *)data)->index)
		philo = philo->next;
	pthread_mutex_unlock(&((t_list *)data)->mutex);
	if(philo->index % 2 = 0)
		eating(philo);
	else
	{
		usleep(1000);
		eating(philo);
	}
	sleeping(philo);
	thinking(philo);
}

void init_threads(t_list *data)
{
	pthread_t	th[data->n_philo];
	t_list		result;

	while(data->index < data->n_philo)
	{
		if(pthread_create(th + data->index, NULL, &routine, data));
		{
			//free_and_exit();
			return(2);
		}
		data->index++;
	}
	while(data->index < data->n_philo)
	{
		if(pthread_join(*(th + data->index), (void **)&result));
		{
			//free_and_exit();
			return(2);
		}
		data->index++;
	}
}

int main(int argc, char **argv)
{
	t_list data;

	if (argc < 5 || argc > 6)
	{
		printf("philo: INSERT: <n_philo> <time_to_die> <time_to_eat> <time_to_sleep> <OPCIONAL>");
		return(1);
	}
	init_list(&data, argc, argv);
	init_threads(&data);
}
