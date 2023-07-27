/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:38:12 by rimarque          #+#    #+#             */
/*   Updated: 2023/07/27 17:57:32 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void take_forks_odd(t_node *philo)
{
	pthread_mutex_lock(&philo->fork.mutex);
	ft_print(philo, "has taken a fork", GREEN);
	pthread_mutex_lock(&philo->next->fork.mutex);
	ft_print(philo, "has taken a fork", GREEN);
}

void take_forks_even(t_node *philo)
{
	pthread_mutex_lock(&philo->next->fork.mutex);
	ft_print(philo, "has taken a fork", GREEN);
	pthread_mutex_lock(&philo->fork.mutex);
	ft_print(philo, "has taken a fork", GREEN);
}

int	eat(t_node *philo)
{
	philo->time_no_eat = program_time(philo->data) - philo->last_eat;
	philo->last_eat = program_time(philo->data);
	if(philo->time_no_eat > philo->data->time_die)
	{
		pthread_mutex_lock(&philo->data->mutex_status);
		philo->status = DEAD;
		pthread_mutex_unlock(&philo->data->mutex_status);
		return(-1);
	}
	pthread_mutex_lock(&philo->data->mutex_status);
	philo->status = EATING;
	pthread_mutex_unlock(&philo->data->mutex_status);
	ft_print(philo, "is eating", GREEN);
	ft_usleep(philo, philo->data->time_eat);
	return(0);
}

void	drop_forks(t_node *philo)
{
		pthread_mutex_unlock(&philo->fork.mutex);
		pthread_mutex_unlock(&philo->next->fork.mutex);
}

int	meal(t_node *philo)
{
	if(philo->id % 2 == 0)
	{
			take_forks_even(philo);
			if(eat(philo) == -1)
				return(-1);
			drop_forks(philo);
	}
	else
	{
		if(philo->data->n_philo % 2 != 0 && philo->data->dif >= 0)
			ft_usleep(philo, philo->data->dif + 10);
		take_forks_odd(philo);
		if(eat(philo) == -1)
			return(-1);
		drop_forks(philo);
	}
	return(0);
}
