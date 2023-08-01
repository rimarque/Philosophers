/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:38:12 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/01 02:48:55 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void take_forks_odd(t_node *philo)
{
	pthread_mutex_lock(&philo->fork);
	ft_print(philo, "has taken a fork", GREEN);
	pthread_mutex_lock(&philo->prev->fork);
	ft_print(philo, "has taken a fork", GREEN);
}

void take_forks_even(t_node *philo)
{
	pthread_mutex_lock(&philo->prev->fork);
	ft_print(philo, "has taken a fork", GREEN);
	pthread_mutex_lock(&philo->fork);
	ft_print(philo, "has taken a fork", GREEN);
}

int	eat(t_node *philo)
{
	pthread_mutex_lock(&philo->time);
	philo->last_eat = program_time(philo->data);
	pthread_mutex_unlock(&philo->time);
	pthread_mutex_lock(&philo->eat);
	philo->n_eat++;
	pthread_mutex_unlock(&philo->eat);
	if(ft_print(philo, "is eating", GREEN) == -1)
		return(0);
	ft_usleep(philo, philo->data->time_eat);
	return(0);
}

void	drop_forks(t_node *philo)
{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->prev->fork);
}

int	meal(t_node *philo)
{
	if(philo->id % 2 == 0)
	{
		take_forks_even(philo);
		eat(philo);
		drop_forks(philo);
	}
	else
	{
		if(philo->data->n_philo % 2 != 0 && philo->data->dif >= 0)
			ft_usleep(philo, philo->data->dif + 10);
		take_forks_odd(philo);
		eat(philo);
		drop_forks(philo);
	}
	return(0);
}
