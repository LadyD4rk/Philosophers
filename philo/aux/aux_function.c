/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:43:42 by jobraga-          #+#    #+#             */
/*   Updated: 2025/10/10 14:21:38 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

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

void	print_write(char *str, t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->data->mutex.write_flag);
	time = ft_get_time() - philo->start_time;
	printf("%ld %i %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->mutex.write_flag);
}
