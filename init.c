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

void create_list(t_list *data)
{
	int count;
	t_node *new;

	count = 1;
	while(count <= data->n_philo)
	{
		new = create_node(count, data);
		insert_last(data, new);
		count++;
	}
}

void init_list(t_list *data, int argc, char **argv)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	data->time_boot = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	data->n_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		data->n_eat = -1;
	if (argc == 6)
		data->n_eat = ft_atoi(argv[5]);
	data->index = 0;
	data->head = NULL;
	data->flag = 0;
	pthread_mutex_init(&data->mutex_print, NULL);
	pthread_mutex_init(&data->mutex_even, NULL);
	pthread_mutex_init(&data->mutex_odd, NULL);
	pthread_mutex_init(&data->mutex_think, NULL);
	create_list(data);
}
