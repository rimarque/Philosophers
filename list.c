/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:52:58 by rimarque          #+#    #+#             */
/*   Updated: 2023/07/14 17:32:21 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_node *create_node(int count)
{
	t_node *new;

	new = malloc(sizeof(t_node));
	if (!new)
		return(NULL);
	new->index = count;
	new->fork.status = DROPED;
	pthread_mutex_init(&new->fork.mutex, NULL);
	new->status = THINKING;
	//pthread_mutex_init(&new->mutex, NULL);
	new->last_eat = 0;
	return(new);
}

void	insert_last(t_list *stack, t_node *new)
{
	if (stack->head == NULL)
	{
		stack->head = new;
		new->next = stack->head;
		new->prev = stack->head;
	}
	else
	{
		stack->head->prev->next = new;
		new->prev = stack->head->prev;
		new->next = stack->head;
		stack->head->prev = new;
	}
}

void	free_list(t_list *data)
{
	t_node	*element;
	t_node	*temp;
	int		counter;

	if (data->head == NULL)
		return ;
	element = data->head;
	counter = 0;
	while (counter++ < data->n_philo)
	{
		temp = element;
		element = element->next;
		pthread_mutex_destroy(&element->fork.mutex);
		free(temp);
	}
	data->head = NULL;
}

