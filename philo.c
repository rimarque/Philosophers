/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:02:44 by rimarque          #+#    #+#             */
/*   Updated: 2023/07/18 22:45:36 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int program_time(t_list *data)
{
	struct timeval	current_time;
	int				program_time;

	gettimeofday(&current_time, NULL);
	program_time = ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000)) - data->time_boot;
	return(program_time);
}

void take_forks_even(t_node *philo)
{
	pthread_mutex_lock(&philo->fork.mutex);
	philo->fork.status = USING;
	pthread_mutex_lock(&philo->data->mutex);
	printf("(%d): Philo %d as taken a fork\n", program_time(philo->data), philo->index);
	pthread_mutex_unlock(&philo->data->mutex);
	pthread_mutex_lock(&philo->prev->fork.mutex);
	philo->prev->fork.status = USING;
	pthread_mutex_lock(&philo->data->mutex);
	printf("(%d): Philo %d as taken a fork\n", program_time(philo->data), philo->index);
	pthread_mutex_unlock(&philo->data->mutex);
}

void take_forks_odd(t_node *philo)
{
	pthread_mutex_lock(&philo->prev->fork.mutex);
	philo->prev->fork.status = USING;
	pthread_mutex_lock(&philo->data->mutex);
	printf("(%d): Philo %d as taken a fork\n", program_time(philo->data), philo->index);
	pthread_mutex_unlock(&philo->data->mutex);
	pthread_mutex_lock(&philo->fork.mutex);
	philo->fork.status = USING;
	pthread_mutex_lock(&philo->data->mutex);
	printf("(%d): Philo %d as taken a fork\n", program_time(philo->data), philo->index);
	pthread_mutex_unlock(&philo->data->mutex);
}

void	ft_usleep(t_node *philo, int time)
{
	int finish_time;

	finish_time = program_time(philo->data) + time;
	while(program_time(philo->data) < finish_time)
	{
		usleep(1000);
	}
}

void	eating(t_node *philo)
{
	philo->time_no_eat = program_time(philo->data) - philo->last_eat;
	philo->last_eat = program_time(philo->data);
	if(philo->time_no_eat > philo->data->time_die)
	{
		philo->status = DEAD;
		pthread_mutex_lock(&philo->data->mutex);
		printf("(%d): Philo %d is dead\n", program_time(philo->data), philo->index);
		pthread_mutex_unlock(&philo->data->mutex);
	}
	philo->status = EATING;
	ft_usleep(philo, philo->data->time_eat);
	pthread_mutex_lock(&philo->data->mutex);
	printf("(%d): Philo %d is eating\n", program_time(philo->data), philo->index);
	pthread_mutex_unlock(&philo->data->mutex);
}

void	drop_forks(t_node *philo)
{
	philo->prev->fork.status = DROPED;
	pthread_mutex_lock(&philo->data->mutex);
	printf("(%d): Philo %d has droped a fork\n", program_time(philo->data), philo->index);
	pthread_mutex_unlock(&philo->data->mutex);
	pthread_mutex_unlock(&philo->prev->fork.mutex);
	philo->fork.status = DROPED;
	pthread_mutex_lock(&philo->data->mutex);
	printf("(%d): Philo %d has droped a fork\n", program_time(philo->data), philo->index);
	pthread_mutex_unlock(&philo->data->mutex);
	pthread_mutex_unlock(&philo->fork.mutex);
}

void	sleeping(t_node *philo)
{
	philo->status = SLEEPING;
	ft_usleep(philo, philo->data->time_sleep);
	pthread_mutex_lock(&philo->data->mutex);
	printf("(%d): Philo %d is sleeping\n", program_time(philo->data), philo->index);
	pthread_mutex_unlock(&philo->data->mutex);
}

void	thinking(t_node *philo)
{
	philo->status = THINKING;
	pthread_mutex_lock(&philo->data->mutex);
	printf("(%d): Philo %d is thinking\n", program_time(philo->data), philo->index);
	pthread_mutex_unlock(&philo->data->mutex);
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
		}
		philo = philo->next;
		count++;
	}
	return (0);
}*/

void	*routine(void *pointer)
{
	t_node *philo;

	//data = (t_list *) malloc(sizeof((t_list *)pointer));
	//data = ((t_list *)pointer);
	/*pthread_mutex_lock(&((t_list *)pointer)->mutex);
	if (data->flag == 0)
		data->flag = 1;
	else
		rotate(data);
	pthread_mutex_unlock(&((t_list *)pointer)->mutex);*/
	philo = malloc(sizeof(t_node));
	philo = (t_node *)pointer;
	pthread_mutex_lock(&((t_node *)pointer)->mutex);
	printf("philo id: %d\n", philo->index);
	pthread_mutex_unlock(&((t_node *)pointer)->mutex);
	//while(check_death(*data) || philo->time_no_eat < ((t_list *)data)->time_die)
	while(1)
	{
		//printf("oi\n");
		if(philo->index % 2 == 0)
		{
			take_forks_even(philo);
			eating(philo);
			drop_forks(philo);
		}
		else
		{
			usleep(philo->data->time_eat * 1000 / 2);
			take_forks_odd(philo);
			eating(philo);
			drop_forks(philo);
		}
		sleeping(philo);
		thinking(philo);
	}
	return(NULL);
}

void init_threads(t_list *data)
{
	pthread_t	th[data->n_philo];
	//t_list		result;
	t_node		*philo;
	int count;

	philo = (t_node *) malloc(sizeof(t_node));
	philo = data->head;
	/*if(pthread_create(th + data->index, NULL, &routine, philo))
	{
		printf("create thread malfuntction");
		exit(2); //FUNCTION NOT ALLOWED
	}*/
	count = 0;
	//printf("n_philo = %d\n", data->n_philo);
	while(count++ < data->n_philo)
	{
		//printf("create thread with id = %d\n", philo->index);
		//if(data->index == 0)
		//	usleep(data->time_eat * 1000 / 500);
		if(pthread_create(th + data->index, NULL, &routine, philo))
		{
			printf("create thread malfuntction");
			exit(2); //FUNCTION NOT ALLOWED
		}
		philo = philo->next;
	}
	//THREAD CHECK DEATH
	//THREAD CHECK FULL
	count = 0;
	while(count++ < data->n_philo)
	{
		if(pthread_join(*(th + data->index), NULL))
		{
			printf("join thread malfuntction");
			exit(2);
		}
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
