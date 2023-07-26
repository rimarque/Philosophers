/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:38:12 by rimarque          #+#    #+#             */
/*   Updated: 2023/07/26 23:47:32 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void take_forks_odd(t_node *philo)
{
	pthread_mutex_lock(&philo->fork.mutex);
	ft_print(philo, "has taken a fork", GREEN);
	pthread_mutex_lock(&philo->prev->fork.mutex);
	ft_print(philo, "has taken a fork", GREEN);
}

void take_forks_even(t_node *philo)
{
	pthread_mutex_lock(&philo->prev->fork.mutex);
	ft_print(philo, "has taken a fork", GREEN);
	pthread_mutex_lock(&philo->fork.mutex);
	ft_print(philo, "has taken a fork", GREEN);
}

void	eat(t_node *philo)
{
	philo->time_no_eat = program_time(philo->data) - philo->last_eat;
	philo->last_eat = program_time(philo->data);
	if(philo->time_no_eat > philo->data->time_die)
	{
		philo->status = DEAD;
		printf("philo %d is dead\n", philo->id);
	}
	philo->status = EATING;
	ft_print(philo, "is eating", GREEN);
	ft_usleep(philo, philo->data->time_eat);
}

void	drop_forks(t_node *philo)
{
		pthread_mutex_unlock(&philo->fork.mutex);
		pthread_mutex_unlock(&philo->prev->fork.mutex);
}

void	meal(t_node *philo)
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
}
