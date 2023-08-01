/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:43:51 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/01 22:48:49 by rimarque         ###   ########.fr       */
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
		pthread_mutex_lock(&philo->data->mutex_end);
		if(philo->data->end == -1)
		{
			pthread_mutex_unlock(&philo->data->mutex_end);
			return(NULL);
		}
		else
			pthread_mutex_unlock(&philo->data->mutex_end);
		count = 0;
		while (count++ < philo->data->n_philo)
		{
			pthread_mutex_lock(&philo->eat);
			if(philo->n_eat == philo->data->n_eat)
			{
				philo->n_eat = -1;
				n_full++;
			}
			pthread_mutex_unlock(&philo->eat);
			philo = philo->next;
		}
	}
	pthread_mutex_lock(&philo->data->mutex_end);
	philo->data->end = 1;
	pthread_mutex_unlock(&philo->data->mutex_end);
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
			pthread_mutex_lock(&philo->data->mutex_end);
			if(philo->data->end == 1)
			{
				pthread_mutex_unlock(&philo->data->mutex_end);
				return(NULL);
			}
			else
				pthread_mutex_unlock(&philo->data->mutex_end);
			set_time(philo);
			if(philo->time_no_eat > philo->data->time_die)
			{
				set_arg(&philo->data->end, -1, &philo->data->mutex_end);
				ft_usleep(philo, 1);
				ft_print(philo, "died", RED);
				return (NULL);
			}
			philo = philo->next;
		}
	}
	return (NULL);
}
