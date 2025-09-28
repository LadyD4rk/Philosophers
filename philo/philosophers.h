/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:31:57 by jobraga-          #+#    #+#             */
/*   Updated: 2025/09/26 12:57:10 by jobraga-         ###   ########.fr       */
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

typedef struct s_time
{
	int			time_eat;
	int			time_die;
	int			time_sleep;
	int			count_eat;
	long		start_time;
}				t_time;

typedef struct s_philo
{
	pthread_t	philo;
	t_time		time;
	int			id;
	int			tm_die;
	int			tm_eat;
	int			tm_sleep;
	int			count_eat;
	int			die;
	long		last_eat;
}				t_philo;

typedef struct s_data
{
	t_philo		*table;
	t_time		time;
}				t_data;

void	clock_(t_time *time);

// aux.c
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *str);
int		is_valid_argument(int ac, char **av);

//create_table.c
void	create_table(t_philo *table, t_time time, int count_philo, char **av);

//clock_time.c
long	ft_get_time(void);
void	create_time(t_time *time, char **av);

//main.c
void	clear_table(t_philo *table, int count_philo);

#endif