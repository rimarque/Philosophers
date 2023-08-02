/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:02:33 by rimarque          #+#    #+#             */
/*   Updated: 2023/07/18 11:02:33 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_node	*create_n(int count, t_list *data)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
	{
		printf("philo: error memory allocation by create_n by malloc\n");
		return (NULL);
	}
	new->id = count;
	new->n_eat = 0;
	pthread_mutex_init(&new->fork, NULL);
	pthread_mutex_init(&new->time, NULL);
	pthread_mutex_init(&new->eat, NULL);
	new->last_eat = 0;
	new->data = data;
	return (new);
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

int	create_l(t_list *data)
{
	int		count;
	t_node	*new;

	count = 1;
	while (count <= data->n_philo)
	{
		new = create_n(count, data);
		if (!new)
			return (1);
		insert_last(data, new);
		count++;
	}
	return (0);
}

int	init_l(t_list *data, int argc, char **argv)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	data->time_boot = (current_time.tv_sec * 1000)
		+ (current_time.tv_usec / 1000);
	data->n_philo = ft_atol(argv[1]);
	data->time_die = ft_atol(argv[2]);
	data->time_eat = ft_atol(argv[3]);
	data->time_sleep = ft_atol(argv[4]);
	if (argc == 5)
		data->n_eat = -1;
	if (argc == 6)
		data->n_eat = ft_atol(argv[5]);
	data->head = NULL;
	data->dif = data->time_eat - data->time_sleep;
	data->end = 0;
	data->n_full = 0;
	pthread_mutex_init(&data->mutex_print, NULL);
	pthread_mutex_init(&data->mutex_end, NULL);
	if (create_l(data))
		return (1);
	return (0);
}
