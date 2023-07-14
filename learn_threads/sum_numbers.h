/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sum_numbers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:44:16 by rimarque          #+#    #+#             */
/*   Updated: 2023/07/12 18:27:53 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUM_NUMBERS_H
# define SUM_NUMBERS_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct s_primes
{
	int flag;
	int index;
	int *array;
}t_primes;

#endif
