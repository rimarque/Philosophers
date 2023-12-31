/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:55:30 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/03 20:01:52 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_n(t_node *philo)
{
	pthread_mutex_destroy(&philo->fork);
	pthread_mutex_destroy(&philo->time);
	pthread_mutex_destroy(&philo->eat);
}

void	destroy_l(t_list *data)
{
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_end);
}

void	free_destroy_l(t_list *data)
{
	t_node	*element;
	t_node	*temp;
	int		counter;

	destroy_l(data);
	free(data->th);
	if (data->head == NULL)
		return ;
	element = data->head;
	counter = 0;
	while (counter++ < data->size)
	{
		destroy_n(element);
		temp = element;
		element = element->next;
		free(temp);
	}
	data->head = NULL;
}
