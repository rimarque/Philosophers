/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:31:58 by rimarque          #+#    #+#             */
/*   Updated: 2023/07/22 11:24:30 by rimarque         ###   ########.fr       */
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

struct s_list;

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
	pthread_mutex_t	mutex;
	pthread_mutex_t	*mutex_even;
	pthread_mutex_t	*mutex_odd;
	pthread_mutex_t	mutex_fork;
	struct s_node	*next;
	struct s_list	*data;
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
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_even;
	pthread_mutex_t	mutex_odd;
	pthread_mutex_t	mutex_fork;
	//pthread_mutex_t	mutex_think;
	int flag;
}t_list;

void init_list(t_list *data, int argc, char **argv);
int	ft_atoi(const char *str);
t_node *create_node(int count, t_list *data);
void	insert_last(t_list *stack, t_node *new);
void	rotate(t_list *stack);

#endif
