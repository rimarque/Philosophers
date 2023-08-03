/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:57:28 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/03 19:52:58 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_list *data,
	pthread_t *th_death, pthread_t *th_full)
{
	t_node		*philo;
	int			count;

	philo = data->head;
	count = 0;
	while (count < data->n_philo)
	{
		if (pthread_create(&data->th[count], NULL, &routine, philo))
			return (1);
		count++;
		philo = philo->next;
	}
	if (data->n_eat > 0)
	{
		if (pthread_create(th_full, NULL, &check_full, data))
			return (2);
	}
	if (pthread_create(th_death, NULL, &check_death, data))
		return (3);
	return (0);
}

int	join_threads(t_list *data, pthread_t *th_death,
	pthread_t *th_full)
{
	t_node	*philo;
	int		count;

	philo = data->head;
	count = 0;
	while (count < data->n_philo)
	{
		if (pthread_join(data->th[count], NULL))
			return (1);
		count++;
		philo = philo->next;
	}
	if (data->n_eat > 0)
	{
		if (pthread_join(*th_full, NULL))
			return (2);
	}
	if (pthread_join(*th_death, NULL))
		return (3);
	return (0);
}

int	handle_error_t(int result, char *f, t_list *data)
{
	if (result == 0)
		return (0);
	else if (result == 1)
		printf("philo: philo thread(s) malfuntction by %s\n", f);
	else if (result == 2)
		printf("philo: check full thread malfuntction by %s\n", f);
	else if (result == 3)
		printf("philo: check death thread malfuntction by %s\n", f);
	free_destroy_l(data);
	return (1);
}

int	create_join_th(t_list *data)
{
	pthread_t	th_death[1];
	pthread_t	th_full[1];
	int			result;

	result = create_threads(data, th_death, th_full);
	if (handle_error_t(result, "pthread_create", data) != 0)
		return (1);
	result = join_threads(data, th_death, th_full);
	if (handle_error_t(result, "pthread_join", data) != 0)
		return (2);
	return (0);
}
