/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:46:56 by rimarque          #+#    #+#             */
/*   Updated: 2023/07/26 22:33:50 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_node *philo)
{
	philo->status = SLEEPING;
	ft_print(philo, "is sleeping", CYAN);
	ft_usleep(philo, philo->data->time_sleep);
}

void	thinking(t_node *philo)
{
	philo->status = THINKING;
	ft_print(philo, "is thinking", WHITE);
}

void	*routine(void *pointer)
{
	t_node *philo;

	philo = malloc(sizeof(t_node));
	philo = (t_node *)pointer;
	if (philo->id % 2 != 0)
		ft_usleep(philo, 1);
	while(1)
	{
		if(philo->status == DEAD) // || data->flag == 1)
			return(NULL);
		meal(philo);
		sleeping(philo);
		thinking(philo);
	}
	free(philo);
	return(NULL);
}
