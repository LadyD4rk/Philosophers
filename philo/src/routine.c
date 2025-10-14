/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:13:41 by jobraga-          #+#    #+#             */
/*   Updated: 2025/10/14 11:50:21 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_write("has taken a fork", philo);
		pthread_mutex_lock(philo->l_fork);
		print_write("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_write("has taken a fork", philo);
		pthread_mutex_lock(philo->r_fork);
		print_write("has taken a fork", philo);
	}
}

void	philo_eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->data->mutex.meat_flag);
	philo->last_eat_time = ft_get_time();
	philo->count_eat++;
	pthread_mutex_unlock(&philo->data->mutex.meat_flag);
	print_write("is eating", philo);
	ft_usleep(philo->data->args.time_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_dream(t_philo *philo)
{
	print_write("is sleeping", philo);
	ft_usleep(philo->data->args.time_sleep);
}

void	philo_think(t_philo *philo)
{
	print_write("is thinking", philo);
}

/* ◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died */
