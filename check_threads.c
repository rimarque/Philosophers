/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:43:51 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/01 03:26:07 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_full(void *data)
{
	t_node	*philo;
	int		count;
	int		n_full;

	philo = (*(t_list *)data).head;
	n_full = 0;
	while(n_full < philo->data->n_philo)
	{
		count = 0;
		while (count++ < philo->data->n_philo)
		{
			pthread_mutex_lock(&philo->eat);
			if(philo->n_eat == philo->data->n_eat)
			{
				n_full++;
				pthread_mutex_unlock(&philo->eat);
			}
			else
				pthread_mutex_unlock(&philo->eat);
			philo = philo->next;
		}
	}
	pthread_mutex_lock(&philo->data->mutex_full);
	philo->data->full = 1;
	pthread_mutex_unlock(&philo->data->mutex_full);
	return (NULL);
}

void *check_death(void *data)
{
	t_node	*philo;
	int		count;

	philo = (*(t_list *)data).head;
	while(1)
	{
		count = 0;
		while (count++ < philo->data->n_philo)
		{
			pthread_mutex_lock(&philo->time);
			philo->time_no_eat = program_time(philo->data) - philo->last_eat;
			pthread_mutex_unlock(&philo->time);
			if(philo->time_no_eat > philo->data->time_die)
			{
				pthread_mutex_lock(&philo->data->mutex_end);
				philo->data->end = -1;
				pthread_mutex_unlock(&philo->data->mutex_end);
				ft_usleep(philo, 1);
				ft_print(philo, "died", RED);
				return (NULL);
			}
			philo = philo->next;
		}
	}
	return (NULL);
}

/*void *check_death(void *data)
{
	t_node	**philo;
	int		count;

	//philo = (t_node *)pointer;
	philo = &(*(t_list *)data).head;
	while(1)
	{
		count = 0;
		while (count++ < (**philo).data->n_philo)
		{
			pthread_mutex_lock(&(**philo).data->mutex_time);
			(**philo).time_no_eat = program_time((**philo).data) - (**philo).last_eat;
			pthread_mutex_unlock(&(**philo).data->mutex_time);
			if((**philo).time_no_eat > (**philo).data->time_die)
			{
				pthread_mutex_lock(&(**philo).data->mutex_death);
				(**philo).data->death = -1;
				pthread_mutex_unlock(&(**philo).data->mutex_death);
				ft_usleep(*philo, 1);
				ft_print(*philo, "died", RED);
				return (NULL);
			}
			philo = &(**philo).next;
		}
	}
	return (NULL);
}*/

