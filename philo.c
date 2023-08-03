/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:02:44 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/03 19:59:13 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_error_arg(int argc, char **argv)
{
	int	i;

	if (check_n_arg(argc))
		return (1);
	i = 1;
	while (i < argc)
	{
		if (check_nbr(argv[i]))
			return (1);
		if (check_sign(ft_atol(argv[i])))
			return (1);
		if (check_int(ft_atol(argv[i])))
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_list	data;

	if (check_error_arg(argc, argv))
		return (1);
	if (init_l(&data, argc, argv))
	{
		free_destroy_l(&data);
		return (2);
	}
	if (create_join_th(&data))
	{
		free_destroy_l(&data);
		return (3);
	}
	free_destroy_l(&data);
	return (0);
}
