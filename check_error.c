/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:15:39 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/02 23:13:41 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_n_arg(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("philo: please insert: <n_philo> <time_to_die> ");
		printf("<time_to_eat> <time_to_sleep> <OPCIONAL(n_eat)>\n");
		return (1);
	}
	return (0);
}

int	check_nbr(const char *str)
{
	if (ft_strlen(str) > 11)
	{
		printf("philo: please insert smaller number\n");
		return (1);
	}
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
	{
		printf("philo: please insert only numbers\n");
		return (1);
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
		{
			printf("philo: please insert only numbers\n");
			return (1);
		}
		str++;
	}
	return (0);
}

int	check_sign(long long nbr)
{
	if (nbr <= 0)
	{
		printf("philo: please insert positive number\n");
		return (1);
	}
	return (0);
}

int	check_int(long long nbr)
{
	if (nbr > 2147483647 || nbr < -2147483648)
	{
		printf("philo: please insert smaller number\n");
		return (1);
	}
	return (0);
}
