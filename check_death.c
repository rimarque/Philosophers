/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:43:51 by rimarque          #+#    #+#             */
/*   Updated: 2023/07/27 18:53:55 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *check_death(void *pointer)
{
	t_node	*philo;

	philo = (t_node *)pointer;
	while(1)
	{
		pthread_mutex_lock(&philo->data->mutex_status);
		if(philo->status == DEAD)
		{
			pthread_mutex_lock(&philo->data->mutex_print);
			printf("%s%ld %d %s%s\n", RED, program_time(philo->data), philo->id, "died", RESET);
			pthread_mutex_unlock(&philo->data->mutex_print);
			//ft_print(philo, "died", RED);
			pthread_mutex_lock(&philo->data->mutex_death);
			philo->data->death = -1;
			pthread_mutex_unlock(&philo->data->mutex_death);
			pthread_mutex_unlock(&philo->data->mutex_status);
			return (NULL);
		}
		else
			pthread_mutex_unlock(&philo->data->mutex_status);
	}
	return (NULL);
}

/*void *check_death_old(void *pointer)
{
	t_node	*philo;
	int		count;

	philo = (t_node *)pointer;
	temp = philo;
	while(1)
	{
		count = 0;
		while (count++ < philo->data->n_philo)
		{
			pthread_mutex_lock(&philo->data->mutex_status);
			if(temp->status == DEAD)
			{
				pthread_mutex_lock(&philo->data->mutex_print);
				printf("%s%ld %d %s%s\n", RED, program_time(philo->data), philo->id, "died", RESET);
				pthread_mutex_unlock(&philo->data->mutex_print);
				//ft_print(philo, "died", RED);
				pthread_mutex_lock(&philo->data->mutex_death);
				philo->data->death = -1;
				pthread_mutex_unlock(&philo->data->mutex_death);
				pthread_mutex_unlock(&philo->data->mutex_status);
				return (NULL);
			}
			else
				pthread_mutex_unlock(&philo->data->mutex_status);
			temp = temp->next;
		}
	}
	return (NULL);
}*/

void *check_full(void *data)
{
		t_node	*philo;
	int		count;

	philo = malloc(sizeof(t_node));
	philo = (*(t_list *)data).head;
	while(1)
	{
		count = 0;
		while (count++ < (*(t_list *)data).n_philo)
		{
			if(philo->status == DEAD)
			{
				pthread_mutex_lock(&philo->data->mutex_death);
				printf("DEATH IN DEATH: %d\n", philo->data->death);
				pthread_mutex_unlock(&philo->data->mutex_death);
				ft_print(philo, "died", RED);
				philo->data->death = -1;
			}
			philo = philo->next;
		}
	}
	return (NULL);
}
