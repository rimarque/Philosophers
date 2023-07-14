#include "philo.h"

void create_list(t_list *data)
{
	int count;
	t_node *new;

	count = 1;
	while(count <= data->n_philo)
	{
		new = create_node(count);
		insert_last(data, new);
		count++;
	}
}

void init_list(t_list *data, int argc, char **argv)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	data->time_boot = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	data->n_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		data->n_eat = -1;
	if (argc == 6)
		data->n_eat = ft_atoi(argv[5]);
	data->index = 0;
	data->head = NULL;
	pthread_mutex_init(&data->mutex, NULL);
	create_list(data);
}
int program_time(t_list data)
{
	struct timeval	current_time;
	int				program_time;

	gettimeofday(&current_time, NULL);
	program_time = ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000)) - data.time_boot;
	return(program_time);
}

void take_forks_even(t_node *philo, t_list data)
{
	pthread_mutex_lock(&philo->fork.mutex);
	philo->fork.status = USING;
	printf("(%d): Philo %d as taken a fork\n", program_time(data), philo->index);
	pthread_mutex_lock(&philo->prev->fork.mutex);
	philo->prev->fork.status = USING;
	printf("(%d): Philo %d as taken a fork\n", program_time(data), philo->prev->index);
}

void take_forks_odd(t_node *philo, t_list data)
{
	pthread_mutex_lock(&philo->prev->fork.mutex);
	philo->prev->fork.status = USING;
	printf("(%d): Philo %d as taken a fork\n", program_time(data), philo->index);
	pthread_mutex_lock(&philo->fork.mutex);
	philo->fork.status = USING;
	printf("(%d): Philo %d as taken a fork\n", program_time(data), philo->index);
}

void	eating(t_node *philo, t_list data)
{
	philo->time_no_eat = program_time(data) - philo->last_eat;
	if(philo->time_no_eat > data.time_die)
	{
		philo->status = DEAD;
		printf("(%d): Philo %d is dead\n", program_time(data), philo->index);
		exit(1);
	}
	philo->last_eat = program_time(data);
	philo->status = EATING;
	printf("(%d): Philo %d is eating\n", program_time(data), philo->index);
}

void	drop_forks(t_node *philo, t_list data)
{
	philo->prev->fork.status = DROPED;
	printf("(%d): Philo %d as droped a fork\n", program_time(data), philo->index);
	pthread_mutex_unlock(&philo->prev->fork.mutex);
	philo->fork.status = DROPED;
	printf("(%d): Philo %d as droped a fork\n", program_time(data), philo->index);
	pthread_mutex_unlock(&philo->fork.mutex);
}

/*void	eating(t_node *philo, t_list data)
{
	struct timeval	current_time;
	int				program_time;

	if(philo->time_no_eat > data.time_die)
		philo->status = DEAD;
	pthread_mutex_lock(&philo->fork.mutex);
	philo->fork.status = USING;
	printf("Philo %d as taken a fork", philo->index);
	if(philo->prev->fork.status == DROPED)
	{
		pthread_mutex_lock(&philo->prev->fork.mutex);
		philo->prev->fork.status = USING;
		printf("Philo %d as taken a fork", philo->prev->index);
		philo->status = EATING;
		gettimeofday(&current_time, NULL);
		program_time = current_time.tv_usec - data.time_boot;
		philo->time_no_eat = program_time - philo->last_eat;
		philo->last_eat = program_time;
		printf("Philo %d is eating", philo->index);
		philo->prev->fork.status = DROPED;
		printf("Philo %d as droped a fork", philo->index);
		pthread_mutex_unlock(&philo->prev->fork.mutex);
	}
	philo->fork.status = DROPED;
	printf("Philo %d as droped a fork", philo->index);
	pthread_mutex_unlock(&philo->fork.mutex);
}*/

/*void	eating(t_node *philo, t_list data)
{
	struct timeval	current_time;
	int				program_time;
void
	gettimeofday(&current_time, NULL);
	program_time = current_time.tv_usec - data.time_boot;
	philo->time_no_eat = program_time - philo->last_eat;
	philo->last_eat = program_time;
	if(philo->time_no_eat > data.time_die)
		philo->status = DEAD;
	pthread_mutex_lock(&philo->fork.mutex);
	philo->fork.status = USING;
	printf("Philo %d as taken a fork", philo->index);
	pthread_mutex_lock(&philo->prev->fork.mutex);
	philo->prev->fork.status = USING;
	printf("Philo %d as taken a fork", philo->prev->index);
	philo->status = EATING;
	philo->fork.status = DROPED;
	printf("Philo %d as droped a fork", philo->index);
	pthread_mutex_unlock(&philo->fork.mutex);
	printf("Philo %d is eating", philo->index);
	philo->prev->fork.status = DROPED;
	printf("Philo %d as droped a fork", philo->index);
	pthread_mutex_unlock(&philo->prev->fork.mutex);
}*/

void	sleeping(t_node *philo, t_list data)
{
	pthread_mutex_lock(&philo->fork.mutex);
	philo->status = SLEEPING;
	printf("(%d): Philo %d is sleeping\n", program_time(data), philo->index);
	pthread_mutex_unlock(&philo->fork.mutex);
}

void	thinking(t_node *philo, t_list data)
{
	//pthread_mutex_unlock(&philo->fork.mutex);
	philo->status = THINKING;
	printf("(%d): Philo %d is thinking\n", program_time(data), philo->index);
	//pthread_mutex_unlock(&philo->fork.mutex);
}

/*int check_death(t_list data)
{
	t_node *philo;
	int		count;

	count = 0;
	philo = data.head;
	while (count < data.n_philo)
	{
		if(philo->status == DEAD)
		{
			printf("Philo %d is dead\n", philo->index);
			exit(1);
		}
		philo = philo->next;
		count++;
	}
	return (0);
}*/

void	*routine(void *data)
{
	t_node *philo;
	int count;

	pthread_mutex_lock(&((t_list *)data)->mutex);
	philo = ((t_list *)data)->head;
	count = 0;
	while(count < ((t_list *)data)->index)
	{
		philo = philo->next;
		count++;
	}
	pthread_mutex_unlock(&((t_list *)data)->mutex);
	//while(check_death(*data) || philo->time_no_eat < ((t_list *)data)->time_die)
	while(1)
	{
		if(philo->index % 2 == 0)
		{
			take_forks_even(philo, (*(t_list *)data));
			eating(philo, *(t_list *)data);
			drop_forks(philo, (*(t_list *)data));
		}
		else
		{
			usleep(1000);
			take_forks_odd(philo, (*(t_list *)data));
			eating(philo, *(t_list *)data);
			drop_forks(philo, (*(t_list *)data));
		}
		if(philo->status == DEAD)
		{
			printf("Philo %d is dead\n", philo->index);
			exit(1);
		}
		sleeping(philo, (*(t_list *)data));
		thinking(philo, (*(t_list *)data));
	}
	return(NULL);
}

void init_threads(t_list *data)
{
	pthread_t	th[data->n_philo];
	t_list		result;

	while(data->index < data->n_philo)
	{
		printf("create thread\n");
		if(pthread_create(th + data->index, NULL, &routine, data))
		{
			//free_and_exit();
			exit(2);
		}
		data->index++;
	}
	while(data->index < data->n_philo)
	{
		if(pthread_join(*(th + data->index), (void **)&result))
		{
			//free_and_exit();
			exit(2);
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
	return(0);
}
