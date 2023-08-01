/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:46:56 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/01 17:25:30 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleeping(t_node *philo)
{
	if(ft_print(philo, "is sleeping", CYAN) == -1)
		return(-1);
	ft_usleep(philo, philo->data->time_sleep);
	return(0);
}

int	thinking(t_node *philo)
{
	if(ft_print(philo, "is thinking", WHITE) == -1)
		return(-1);
	return(0);
}

void	*routine(void *pointer)
{
	t_node *philo;

	philo = (t_node *)pointer;
	if (philo->id % 2 != 0)
		ft_usleep(philo, 1);
	while(1)
	{
		pthread_mutex_lock(&philo->data->mutex_end);
		if(philo->data->end != 0)
		{
			pthread_mutex_unlock(&philo->data->mutex_end);
			return(NULL);
		}
		else
			pthread_mutex_unlock(&philo->data->mutex_end);
		meal(philo);
		if(sleeping(philo) == -1)
			return(NULL);
		if(thinking(philo) == -1)
			return(NULL);
	}
	return(NULL);
}
