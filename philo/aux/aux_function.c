/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:43:42 by jobraga-          #+#    #+#             */
/*   Updated: 2025/11/12 00:29:45 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_usleep(t_data *data, int time)
{
	long	start;
	long	elapsed;

	start = ft_get_time();
	while (1)
	{
		if (check_dead(data))
			return ;
		elapsed = ft_get_time() - start;
		if (elapsed >= time)
			break ;
		usleep(1000);
	}
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

	if (check_dead(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->mutex.write_flag);
	time = ft_get_time() - philo->data->start_time;
	printf("%ld %i %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->mutex.write_flag);
}
