/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:31:58 by rimarque          #+#    #+#             */
/*   Updated: 2023/07/14 19:25:43 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define DEAD -1
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
	int				time_no_eat;
	int				last_eat;
	//pthread_mutex_t	mutex;
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
	long int	time_boot;
	pthread_mutex_t	mutex;
}t_list;

int	ft_atoi(const char *str);
t_node *create_node(int count);
void	insert_last(t_list *stack, t_node *new);

#endif
