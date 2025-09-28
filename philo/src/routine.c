/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 12:03:52 by jobraga-          #+#    #+#             */
/*   Updated: 2025/09/28 14:29:03 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	philo_eat(t_philo *philo)
{
	long	time;

	time = ft_get_time() - philo->last_eat;
	printf("%ld %i is eating\n", time, philo->id);
	philo->last_eat = ft_get_time();
	philo->count_eat++;
	ft_usleep(philo->time.time_eat);
}

void	philo_dream(t_philo *philo)
{
	long	time;

	time = ft_get_time() - philo->last_eat;
	printf("%ld %i is sleeping\n", time, philo->id);
	ft_usleep(philo->time.time_sleep);
}

void	philo_think(t_philo *philo)
{
	long	time;

	time = ft_get_time() - philo->last_eat;
	printf("%ld %i is thinking\n", time, philo->id);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (philo->count_eat <= philo->time.count_eat)
	{
		philo_eat(philo);
		philo_dream(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	thread_create(t_data *data, int count_philo)
{
	int		i;

	i = 0;
	while (i < count_philo)
	{
		pthread_create(&data->table[i].philo, NULL, &routine, &data->table[i]);
		i++;
	}
	clear_table(data->table, count_philo);
}

/* ◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died */
