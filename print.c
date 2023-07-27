/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 12:42:28 by rimarque          #+#    #+#             */
/*   Updated: 2023/07/27 18:36:51 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_node *philo, char *msg, char *color)
{
	//if(flag == 1)
	//	return;
	pthread_mutex_lock(&philo->data->mutex_death);
	if(philo->data->death == -1)
			return ;
	pthread_mutex_unlock(&philo->data->mutex_death);
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("%s%ld %d %s%s\n", color, program_time(philo->data), philo->id, msg, RESET);
	pthread_mutex_unlock(&philo->data->mutex_print);
}
