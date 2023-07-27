/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:57:28 by rimarque          #+#    #+#             */
/*   Updated: 2023/07/27 18:55:35 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int detach_threads(t_list *data, pthread_t *th, pthread_t *th_death)
{
	int count;

	count = 0;
	while(count < data->n_philo)
	{
		if(pthread_detach(*(th + count)))
			return(1);
		count++;
	}
	if(pthread_detach(*th_death))
		return(2);
	return(0);
}

int init_threads(t_list *data, pthread_t *th_philo, pthread_t *th_death)
{
	t_node		*philo;
	int			count;

	philo = (t_node *) malloc(sizeof(t_node));
	philo = data->head;
	count = 0;
	while(count < data->n_philo)
	{
		if(pthread_create(th_philo + count, NULL, &routine, philo))
			return (1);
		if(pthread_create(th_death + count, NULL, &check_death, philo))
			return (2);
		count++;
		philo = philo->next;
	}
	//printf("OI\n");
	//THREAD CHECK DEATH
	//THREAD CHECK FULL
	return(0);
}

int join_threads(t_list *data, pthread_t *th, pthread_t *th_death)
{
	int count;

	count = 0;
	while(count < data->n_philo)
	{
		if(pthread_join(*(th + count), NULL))
			return(1);
		count++;
	}
	if(pthread_join(*th_death, NULL))
		return(2);
	return(0);
}


int end_threads(t_list *data, pthread_t *th, pthread_t *th_death)
{
	int result;

	while(1)
	{
		pthread_mutex_lock(&data->mutex_death);
		if(data->death == -1)
		{
			pthread_mutex_unlock(&data->mutex_death);
			break;
		}
		else
			pthread_mutex_unlock(&data->mutex_death);
	}
	//result = join_threads(data, th, th_death);
	result = detach_threads(data, th, th_death);
	return(result);
}

int	error_threads(t_list *data)
{
	pthread_t	th[data->n_philo];
	pthread_t 	th_death[data->n_philo];
	//pthread_t	th_optional;

	//if (init_threads(data, th, &th_death) == 0 && end_threads(data, th, &th_death) == 0)
	//	return(0);
	if (init_threads(data, th, th_death) == 1)
		printf("philo: create philo thread malfuntction\n");
	//else if (init_threads(data, th, &th_death) == 2)
	//	printf("philo: create check death thread malfuntction\n");
	//else if (init_threads(data, th, &th_death) == 3)
	//	printf("philo: create check eat thread malfuntction\n");
	if (end_threads(data, th, th_death) == 1)
		printf("philo: join philo thread malfuntction\n");
	//else if (end_threads(data, th, &th_death) == 2)
	//	printf("philo: join check death thread malfuntction\n");
	//else if (end_threads(data, th, &th_death) == 3)
	//	printf("philo: join check eat thread malfuntction\n");
	return(0);
}