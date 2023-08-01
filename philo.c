/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:02:44 by rimarque          #+#    #+#             */
/*   Updated: 2023/07/31 21:12:06 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_list	data;

	if (argc < 5 || argc > 6) //check_error
	{
		printf("philo: INSERT: <n_philo> <time_to_die> ");
		printf("<time_to_eat> <time_to_sleep> <OPCIONAL(n_eat)>\n");
		return(1);
	}
	init_list(&data, argc, argv);
	if (error_threads(&data) == -1)
		return(2);
	return(0);
}
