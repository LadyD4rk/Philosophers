/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:31:57 by jobraga-          #+#    #+#             */
/*   Updated: 2025/09/24 15:30:28 by jobraga-         ###   ########.fr       */
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

typedef struct	s_philo
{
	pthread_t	philo;
	int			tm_die;
	int			tm_eat;
	int			tm_sleep;
	int			count_eat;
	int			die;
}				t_philo;


typedef struct	s_data
{
	t_philo		*table;
}				t_data;

// aux
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *str);
int		is_valid_argument(int ac, char **av);

#endif