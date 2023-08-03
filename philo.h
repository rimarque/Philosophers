/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:31:58 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/03 19:28:14 by rimarque         ###   ########.fr       */
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

# define RESET "\033[0m"
# define BLACK "\033[1;30m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define CYAN 	"\033[1;36m"
# define WHITE 	"\033[1;37m"

//struct s_list;

typedef struct s_node
{
	struct s_node	*prev;
	int				id;
	int				n_eat;
	long int		time_no_eat;
	long int		last_eat;
	pthread_mutex_t	fork;
	pthread_mutex_t	time;
	pthread_mutex_t	eat;
	struct s_node	*next;
	struct s_list	*data;
}t_node;

typedef struct s_list
{
	t_node			*head;
	int				size;
	int				n_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				n_eat;
	int				dif;
	int				end;
	int				n_full;
	long			time_boot;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_end;
	pthread_t		*th;
}t_list;

//CHECK_ERROR_ARG
int			check_n_arg(int argc);
int			check_nbr(const char *str);
int			check_sign(long long nbr);
int			check_int(long long nbr);

//FT_ATOL
long long	ft_atol(const char *str);

//INIT
int			init_l(t_list *data, int argc, char **argv);

//THREADS
int			create_join_th(t_list *data);

//ROUTINE
void		*routine(void *pointer);

//PRINT
int			ft_print(t_node *philo, char *msg, char *color);

//TIME
long int	program_time(t_list *data);
void		ft_usleep(t_node *philo, int time);

//MEAL
int			meal(t_node *philo);

//CHECK_THREADS
void		*check_death(void *data);
void		*check_full(void *data);

//SET
size_t		ft_strlen(const char *str);
void		set_arg(int *arg, int content, pthread_mutex_t *mutex);
void		set_time_no_eat(t_node *philo);
void		set_time_last_eat(t_node *philo);

//FREE
void		free_destroy_l(t_list *data);

#endif
