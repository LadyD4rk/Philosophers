/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:13:41 by jobraga-          #+#    #+#             */
/*   Updated: 2025/10/09 12:38:09 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	philo_eat(t_philo *philo)
{
	print_write("is eating", philo);
	philo->last_eat_time = ft_get_time();
	philo->count_eat++;
	ft_usleep(philo->data->args.time_eat);
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
