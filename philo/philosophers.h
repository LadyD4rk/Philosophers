/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:23:30 by jobraga-          #+#    #+#             */
/*   Updated: 2025/10/14 10:29:06 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdint.h>

typedef struct s_data t_data;

typedef struct s_mutex
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_flag;
	pthread_mutex_t	dead_flag;
	pthread_mutex_t	meat_flag;
	int				init;
}				t_mutex;

typedef struct s_args
{
	int				count_eat;
	int				count_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
}				t_args;

typedef struct s_philo
{
	t_data			*data;
	pthread_t		philo;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	long			start_time;
	long			last_eat_time;
	int				id;
	int				count_eat;
}				t_philo;

typedef struct s_data
{
	pthread_t		waiter;
	t_args			args;
	t_philo			*philos;
	t_mutex			mutex;
	int				philo_check;
}				t_data;

// aux
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *str);
int		is_valid_argument(int ac, char **av);
void	*ft_calloc(size_t num, size_t tam);

// aux/aux_function.c
void	ft_usleep(int time);
long	ft_get_time(void);
void	print_write(char *str, t_philo *philo);

// init.c
void 	initialize_all(t_data *data, char **av);

// routine.c
void	philo_eat(t_philo *philo);
void	philo_dream(t_philo *philo);
void	philo_think(t_philo *philo);
void	*routine(void *arg);

// start_dinner.c
void	*monitor_dinner(void *arg);
void	start_dinner(t_philo *philos);

#endif