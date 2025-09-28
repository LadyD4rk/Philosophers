/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:03:45 by jobraga-          #+#    #+#             */
/*   Updated: 2025/09/28 13:32:38 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(int time)
{
	usleep(time * 1000);
}

long	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

void	create_time(t_time *time, char **av)
{
	time->time_die = ft_atoi(av[2]);
	time->time_eat = ft_atoi(av[3]);
	time->time_sleep = ft_atoi(av[4]);
	if (av[5])
		time->count_eat = ft_atoi(av[5]);
	else
		time->count_eat = -1;
	time->start_time = ft_get_time();
	(void)time;
}
