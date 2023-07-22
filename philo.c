/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:02:44 by rimarque          #+#    #+#             */
/*   Updated: 2023/07/21 13:44:46 by rimarque         ###   ########.fr       */
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

void take_forks_odd(t_node *philo)
{
	pthread_mutex_lock(&philo->fork.mutex);
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("%d %d has taken a fork\n", program_time(philo->data), philo->index);
	//printf("%d %d has taken a his fork\n", program_time(philo->data), philo->index);
	pthread_mutex_unlock(&philo->data->mutex_print);
	pthread_mutex_lock(&philo->prev->fork.mutex);
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("%d %d has taken a fork\n", program_time(philo->data), philo->index);
	//printf("%d %d has taken %d fork\n", program_time(philo->data), philo->index, philo->prev->index);
	pthread_mutex_unlock(&philo->data->mutex_print);
}

void take_forks_even(t_node *philo)
{
	pthread_mutex_lock(&philo->prev->fork.mutex);
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("%d %d has taken a fork\n", program_time(philo->data), philo->index);
	//printf("%d %d has taken %d fork\n", program_time(philo->data), philo->index, philo->prev->index);
	pthread_mutex_unlock(&philo->data->mutex_print);
	pthread_mutex_lock(&philo->fork.mutex);
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("%d %d has taken a fork\n", program_time(philo->data), philo->index);
	//printf("%d %d has taken his fork\n", program_time(philo->data), philo->index);
	pthread_mutex_unlock(&philo->data->mutex_print);
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
	//printf("Philo: %d, time no eat: %d, last_eat: %d\n", philo->index, philo->time_no_eat, philo->last_eat);
	philo->last_eat = program_time(philo->data);
//	printf("Philo: %d, last_eat: %d\n", philo->index, philo->last_eat);
	if(philo->time_no_eat > philo->data->time_die)
	{
		//printf("Philo: %d, time no eat: %d, time die: %d\n", philo->index, philo->time_no_eat, philo->data->time_die);
		philo->status = DEAD;
		pthread_mutex_lock(&philo->data->mutex_print);
		printf("%d %d died\n", program_time(philo->data), philo->index);
		pthread_mutex_unlock(&philo->data->mutex_print);
		exit(3);
	}
	philo->status = EATING;
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("%d %d is eating\n", program_time(philo->data), philo->index);
	pthread_mutex_unlock(&philo->data->mutex_print);
	ft_usleep(philo, philo->data->time_eat);
}

void take_forks(t_node *philo) //2/4 410/450 200 200;
{
	if(philo->index % 2 != 0)
		pthread_mutex_lock(philo->mutex_odd);
	if(philo->index % 2 == 0)
	{
		//pthread_mutex_lock(philo->mutex_even);
		take_forks_even(philo);
		//pthread_mutex_unlock(philo->mutex_even);
	}
	if(philo->index % 2 != 0)
		pthread_mutex_unlock(philo->mutex_odd);
	if(philo->index % 2 != 0)
	{
		//pthread_mutex_lock(philo->mutex_odd);
		//ft_usleep(philo, philo->data->time_eat / 40);
		take_forks_odd(philo);
		//pthread_mutex_unlock(philo->mutex_odd);
	}
}

void	drop_forks(t_node *philo)
{
	//if(philo->index % 2 == 0)
	{
	//	pthread_mutex_unlock(&philo->prev->fork.mutex);
		//pthread_mutex_lock(&philo->data->mutex_print);
		//printf("%d %d has DROPED %d fork\n", program_time(philo->data), philo->index, philo->prev->index);
		//pthread_mutex_unlock(&philo->data->mutex_print);
	//	pthread_mutex_unlock(&philo->fork.mutex);
		//pthread_mutex_lock(&philo->data->mutex_print);
		//printf("%d %d has DROPED a his fork\n", program_time(philo->data), philo->index);
		//pthread_mutex_unlock(&philo->data->mutex_print);
	}
	//else
	{
		pthread_mutex_unlock(&philo->fork.mutex);
		//pthread_mutex_lock(&philo->data->mutex_print);
		//printf("%d %d has DROPED a his fork\n", program_time(philo->data), philo->index);
		//pthread_mutex_unlock(&philo->data->mutex_print);
		pthread_mutex_unlock(&philo->prev->fork.mutex);
		//pthread_mutex_lock(&philo->data->mutex_print);
		//printf("%d %d has DROPED %d fork\n", program_time(philo->data), philo->index, philo->prev->index);
		//pthread_mutex_unlock(&philo->data->mutex_print);
	}
}

void	sleeping(t_node *philo)
{
	philo->status = SLEEPING;
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("%d %d is sleeping\n", program_time(philo->data), philo->index);
	pthread_mutex_unlock(&philo->data->mutex_print);
	ft_usleep(philo, philo->data->time_sleep);
}

void	thinking(t_node *philo)
{
	philo->status = THINKING;
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("%d %d is thinking\n", program_time(philo->data), philo->index);
	pthread_mutex_unlock(&philo->data->mutex_print);
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

void	*routine_odd(void *pointer)
{
	t_node *philo;

	philo = malloc(sizeof(t_node));
	philo = (t_node *)pointer;
	//pthread_mutex_lock(&((t_node *)pointer)->mutex);
	//printf("philo id: %d\n", philo->index);
	//pthread_mutex_unlock(&((t_node *)pointer)->mutex);
	//if(philo->data->n_philo % 2 != 0 && philo->index == philo->data->n_philo)
	//		usleep(1000);
	//while(check_death(*data) || philo->time_no_eat < ((t_list *)data)->time_die)
	while(1)
	{
		//printf("oi\n");
		if(philo->index % 2 == 0)
		{
			//ft_usleep(philo, 1);
			//ft_usleep(philo, philo->data->time_eat / 50);
			//pthread_mutex_lock(philo->mutex_even);
			take_forks_even(philo);
			//pthread_mutex_unlock(philo->mutex_even);
			eating(philo);
			drop_forks(philo);
		}
		else
		{
			if(philo->index == philo->data->n_philo) //QUANDO HA NUMERO IMPAR DE FILOSOFOS, O ULTIMO ESPERA UM POUCO
			{
				ft_usleep(philo, philo->data->time_eat / (philo->data->n_philo * 10)); //quanto mais threads, menos espero //para que o 1o e ultimo n intercalem, deixando os outros a morrer
				//usleep(1000);
			}
			if(philo->data->n_philo > 3)
				ft_usleep(philo, philo->data->time_eat / (philo->data->n_philo * 10)); //quanto mais threads, menos espero //Para nao fazer par impar misturado (100 ou 10??) ->> testar, ver codigos
			//if(philo->data->n_philo % 2 != 0)
			//	ft_usleep(philo, philo->data->time_eat / 2); //OS IMPARES ESPERAM SÓ QUANDO O N_PHILO E IMPAR
			//ft_usleep(philo, philo->data->time_eat / 2); //OS IMPARES ESPERAM (FUNCIONA PARA 2/3/4/5/6/7/8/10 500/620 200 200)
			//pthread_mutex_lock(philo->mutex_odd);
			take_forks_odd(philo);
			//pthread_mutex_unlock(philo->mutex_odd);
			eating(philo);
			drop_forks(philo);
		}
		sleeping(philo);
		thinking(philo);
	}
	return(NULL);
}

void	*routine_even(void *pointer)
{
	t_node *philo;

	philo = malloc(sizeof(t_node));
	philo = (t_node *)pointer;
	//pthread_mutex_lock(&((t_node *)pointer)->mutex);
	//printf("philo id: %d\n", philo->index);
	//pthread_mutex_unlock(&((t_node *)pointer)->mutex);
	//if(philo->data->n_philo % 2 != 0 && philo->index == philo->data->n_philo)
	//		usleep(1000);
	//while(check_death(*data) || philo->time_no_eat < ((t_list *)data)->time_die)
	while(1)
	{
		//if(philo->data->n_philo > 3 && philo->index % 2 == 0)
		//		ft_usleep(philo, philo->data->time_eat / (philo->data->n_philo * 10));
		take_forks(philo);
		eating(philo);
		drop_forks(philo);
		sleeping(philo);
		//pthread_mutex_lock(&philo->data->mutex_think);
		thinking(philo);
		//pthread_mutex_unlock(&philo->data->mutex_think);
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
	if (data->n_philo % 2 == 0)
	{
		while(count++ < data->n_philo)
		{
			//printf("create thread with id = %d\n", philo->index);
			//if(data->index == 0)
			//	usleep(data->time_eat * 1000 / 500);
			if(pthread_create(th + data->index, NULL, &routine_odd, philo))
			{
				printf("create thread malfuntction\n");
				exit(2); //FUNCTION NOT ALLOWED
			}
			philo = philo->next;
		}
	}
	else
		while(count++ < data->n_philo)
		{
			//printf("create thread with id = %d\n", philo->index);
			//if(data->index == 0)
			//	usleep(data->time_eat * 1000 / 500);
			if(pthread_create(th + data->index, NULL, &routine_odd, philo))
			{
				printf("create thread malfuntction\n");
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
			printf("join thread malfuntction\n");
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
