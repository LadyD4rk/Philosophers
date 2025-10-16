/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:25:39 by jobraga-          #+#    #+#             */
/*   Updated: 2025/10/16 21:55:35 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*monitor_dinner(void *arg)
{
	t_data		*data;
	t_philo		*philos;
	int			id;

	philos = (t_philo *)arg;
	data = philos->data;
	printf("Monitor iniciado!\n");
	while (1)
	{
		id = 0;
		while (id < data->args.count_philo)
		{
			printf("entrou\n");
			pthread_mutex_lock(&data->mutex.meal_flag);
			if (philos[id].count_eat == data->args.count_eat)
			{
				printf("comeu\n");
				printf("flag: %i\n", data->dead_flag);
				data->dead_flag = 1;
				printf("flag: %i\n", data->dead_flag);
				pthread_mutex_unlock(&data->mutex.meal_flag);
				return(NULL);
			}
			else
				pthread_mutex_unlock(&data->mutex.meal_flag);
			id++;
		}
		ft_usleep(1000);
	}
	return(NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	(void)data;
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (data->dead_flag == 0)
	{
		philo_eat(philo);
		if (data->dead_flag == 1)
			break;
		philo_dream(philo);
		if (data->dead_flag == 1)
			break;
		philo_think(philo);
	}
	return (NULL);
}

void	start_dinner(t_philo *philos)
{
	int		id;

	id = 0;
	while (id < philos->data->args.count_philo)
	{
		pthread_create(&philos[id].philo, NULL, &routine, &philos[id]);
		id++;
	}
	pthread_create(&philos->data->waiter, NULL, &monitor_dinner, philos);
}
