/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:23:30 by jobraga-          #+#    #+#             */
/*   Updated: 2025/11/11 23:27:16 by jobraga-         ###   ########.fr       */
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

typedef struct s_data	t_data;

typedef struct s_mutex
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_flag;
	pthread_mutex_t	dead_flag;
	pthread_mutex_t	meal_flag;
	int				init_write_flag;
	int				init_dead_flag;
	int				init_meal_flag;
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
	long			last_eat_time;
	int				id;
	int				count_eat;
	int				limit_eat;
}				t_philo;

typedef struct s_data
{
	pthread_t		waiter;
	t_args			args;
	t_philo			*philos;
	t_mutex			mutex;
	long			start_time;
	int				id_dead;
	int				dead_flag;
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
void	initialize_args(t_args *args, char **av);
int		initialize_mutex2(t_mutex *mutex);
int		initialize_mutex(t_data *data, t_mutex *mutex);
void	initialize_philo(t_philo *philo, int id, t_data *data);
t_philo	*create_table(t_data *data);

// routine.c
void	philo_eat(t_philo *philo);
void	philo_dream(t_philo *philo);
void	philo_think(t_philo *philo);

// start_dinner.c
void	*monitor_dinner(void *arg);
void	start_dinner(t_philo *philos);
void	*routine(void *arg);

// utils_threads.c
int		check_dead(t_data *data);
int		check_limite_eat(t_philo *philos);
int		check_time_to_die(t_philo *philos);

#endif