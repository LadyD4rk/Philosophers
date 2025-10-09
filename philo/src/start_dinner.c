/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:25:39 by jobraga-          #+#    #+#             */
/*   Updated: 2025/10/09 16:17:54 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*monitor_dinner(void *arg)
{
	t_data	*monitor;
	t_philo	*philos;
	int		id;

	monitor = (t_data *)arg;
	philos = monitor->philos;
	id = 0;
	while (pthread_mutex_lock(&monitor->mutex.dead_flag) == 0)
	{
		id = 0;
		while (id < monitor->args.count_philo)
		{
			if (monitor->philos[id].count_eat == monitor->args.count_eat)
			{
				pthread_mutex_unlock(&monitor->mutex.dead_flag);
				break ;
			}
			if (monitor->args.time_die > ft_get_time() - philos[id].last_eat_time)
			{
				pthread_mutex_unlock(&monitor->mutex.dead_flag);
				break;
			}
			id++;
		}
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	while (1)
	{
		philo_eat(philo);
		philo_dream(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	start_dinner(t_philo *philos)
{
	int		id;

	id = 0;
	while (id < philos->data->args.count_eat)
	{
		pthread_create(&philos[id].philo, NULL, &routine, &philos[id]);
		id++;
	}
	//pthread_create(&philos->data->waiter, NULL, &monitor_dinner, &philos->data);
}
