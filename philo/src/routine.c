/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:13:41 by jobraga-          #+#    #+#             */
/*   Updated: 2025/11/12 00:16:24 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	take_forks(t_philo *philo, int id)
{
	if (id % 2 == 0)
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
	take_forks(philo, philo->id);
	pthread_mutex_lock(&philo->data->mutex.meal_flag);
	print_write("is eating", philo);
	philo->last_eat_time = ft_get_time();
	philo->count_eat++;
	if (philo->count_eat == philo->data->args.count_eat)
		philo->limit_eat = 1;
	pthread_mutex_unlock(&philo->data->mutex.meal_flag);
	ft_usleep(philo->data, philo->data->args.time_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_dream(t_philo *philo)
{
	print_write("is sleeping", philo);
	ft_usleep(philo->data, philo->data->args.time_sleep);
}

void	philo_think(t_philo *philo)
{
	print_write("is thinking", philo);
	if (philo->data->args.count_philo % 2 != 0)
		if (philo->data->args.time_eat >= philo->data->args.time_sleep)
			ft_usleep(philo->data, (philo->data->args.time_eat * 2) \
			- philo->data->args.time_sleep);
}
