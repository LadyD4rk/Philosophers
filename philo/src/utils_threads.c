/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:27:37 by jobraga-          #+#    #+#             */
/*   Updated: 2025/10/20 10:04:06 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	check_dead(t_data *data)
{
	int		check;

	pthread_mutex_lock(&data->mutex.dead_flag);
	check = data->dead_flag;
	pthread_mutex_unlock(&data->mutex.dead_flag);
	return (check);
}

int	check_limite_eat(t_philo *philos)
{
	int		id;
	t_data	*data;

	id = 0;
	data = philos->data;
	if (data->args.count_eat == -1)
		return (0);
	pthread_mutex_lock(&data->mutex.meal_flag);
	while (id < data->args.count_philo)
	{
		if (philos[id].limit_eat == 0)
			break ;
		id++;
	}
	if (id == data->args.count_philo)
	{
		pthread_mutex_lock(&data->mutex.dead_flag);
		data->dead_flag = 1;
		pthread_mutex_unlock(&data->mutex.dead_flag);
		pthread_mutex_unlock(&data->mutex.meal_flag);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex.meal_flag);
	return (0);
}

int	check_time_to_die(t_philo *philos)
{
	int		id;
	t_data	*data;

	data = philos->data;
	pthread_mutex_lock(&data->mutex.meal_flag);
	id = 0;
	while (id < data->args.count_philo)
	{
		if (ft_get_time() - philos[id].last_eat_time > data->args.time_die)
		{
			printf("MORREU");
			pthread_mutex_lock(&data->mutex.dead_flag);
			data->dead_flag = 1;
			data->id_dead = id + 1;
			pthread_mutex_unlock(&data->mutex.dead_flag);
			pthread_mutex_unlock(&data->mutex.meal_flag);
			return (1);
		}
		id++;
	}
	pthread_mutex_unlock(&data->mutex.meal_flag);
	return (0);
}
