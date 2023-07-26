/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:29:23 by rimarque          #+#    #+#             */
/*   Updated: 2023/07/26 20:11:40 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int program_time(t_list *data)
{
	struct timeval	current_time;
	long int		program_time;

	gettimeofday(&current_time, NULL);
	program_time = ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000)) - data->time_boot;
	return(program_time);
}

void	ft_usleep(t_node *philo, int time)
{
	int finish_time;

	finish_time = program_time(philo->data) + time;
	while(program_time(philo->data) < finish_time)
		usleep(1000);
}
