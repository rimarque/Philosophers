/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:31:58 by rimarque          #+#    #+#             */
/*   Updated: 2023/07/13 22:19:39 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define THINKING 0
# define EATING 1
# define SLEEPING 2
# define DROPED 3
# define USING 4

typedef struct s_fork
{
	int				status;
	pthread_mutex_t	mutex;
}t_fork;

typedef struct s_node
{
	struct s_node	*prev;
	int				index;
	t_fork			fork;
	int				status;
	struct s_node	*next;
}t_node;

typedef struct s_list
{
	t_node	*head;
	int 	index;
	int		n_philo;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		n_eat;
	pthread_mutex_t	mutex;
}t_list;

int	ft_atoi(const char *str);

#endif
