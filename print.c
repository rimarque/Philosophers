/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 12:42:28 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/02 22:32:04 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_print(t_node *philo, char *msg, char *color)
{
	pthread_mutex_lock(&philo->data->mutex_end);
	if ((philo->data->end == -1 && ft_strcmp(msg, "died"))
		|| philo->data->end == 1)
	{
		pthread_mutex_unlock(&philo->data->mutex_end);
		return (-1);
	}
	else
		pthread_mutex_unlock(&philo->data->mutex_end);
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("%s%ld %d %s%s\n", color, program_time(philo->data),
		philo->id, msg, RESET);
	pthread_mutex_unlock(&philo->data->mutex_print);
	return (0);
}
