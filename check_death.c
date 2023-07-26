/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:43:51 by rimarque          #+#    #+#             */
/*   Updated: 2023/07/27 00:06:22 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *check_death(void *data)
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
