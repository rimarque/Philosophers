/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:09:55 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/02 22:24:14 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	set_arg(int *arg, int content, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*arg = content;
	pthread_mutex_unlock(mutex);
}

void	set_time_no_eat(t_node *philo)
{
	pthread_mutex_lock(&philo->time);
	philo->time_no_eat = program_time(philo->data) - philo->last_eat;
	pthread_mutex_unlock(&philo->time);
}

void	set_time_last_eat(t_node *philo)
{
	pthread_mutex_lock(&philo->time);
	philo->last_eat = program_time(philo->data);
	pthread_mutex_unlock(&philo->time);
}
