/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:46:56 by rimarque          #+#    #+#             */
/*   Updated: 2023/07/27 18:39:11 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_node *philo)
{
	pthread_mutex_lock(&philo->data->mutex_status);
	philo->status = SLEEPING;
	pthread_mutex_unlock(&philo->data->mutex_status);
	ft_print(philo, "is sleeping", CYAN);
	ft_usleep(philo, philo->data->time_sleep);
}

void	thinking(t_node *philo)
{
	pthread_mutex_lock(&philo->data->mutex_status);
	philo->status = THINKING;
	pthread_mutex_unlock(&philo->data->mutex_status);
	ft_print(philo, "is thinking", WHITE);
}

void	*routine(void *pointer)
{
	t_node *philo;

	philo = (t_node *)pointer;
	if (philo->id % 2 != 0)
		ft_usleep(philo, 1);
	while(1)
	{
		if(philo->status == DEAD) // || data->flag == 1)
			return(NULL);
		if(meal(philo) == -1)
			break ;
		sleeping(philo);
		thinking(philo);
	}
	return(NULL);
}
