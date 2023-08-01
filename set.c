/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:09:55 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/01 22:41:08 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_arg(int *arg, int content, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*arg = content;
	pthread_mutex_unlock(mutex);
}

void	set_time(t_node *philo)
{
	pthread_mutex_lock(&philo->time);
	philo->time_no_eat = program_time(philo->data) - philo->last_eat;
	pthread_mutex_unlock(&philo->time);
}

int		cmp_arg(int arg_1, int arg_2, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	if(arg_1 != arg_2)
	{
		pthread_mutex_unlock(mutex);
		return(arg_1 - arg_2);
	}
	else
		pthread_mutex_unlock(mutex);
	return(0);
}
