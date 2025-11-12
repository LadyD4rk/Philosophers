/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:25:39 by jobraga-          #+#    #+#             */
/*   Updated: 2025/11/12 00:00:50 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*monitor_dinner(void *arg)
{
	t_philo		*philos;

	philos = (t_philo *)arg;
	while (1)
	{
		if (check_limite_eat(philos))
			return (NULL);
		if (check_time_to_die(philos))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (!check_dead(data))
	{
		philo_eat(philo);
		if (check_dead(data))
			break ;
		philo_dream(philo);
		if (check_dead(data))
			break ;
		philo_think(philo);
	}
	return (NULL);
}

void	start_dinner(t_philo *philos)
{
	int		id;
	int		num;

	id = 0;
	while (id < philos->data->args.count_philo)
	{
		pthread_create(&philos[id].philo, NULL, &routine, &philos[id]);
		id++;
	}
	pthread_create(&philos->data->waiter, NULL, &monitor_dinner, philos);
	pthread_join(philos->data->waiter, NULL);
	num = philos->data->id_dead;
	if (num > 0)
	{
		pthread_mutex_lock(&philos->data->mutex.write_flag);
		printf("%ld %i died\n", ft_get_time()
			- philos[num - 1].data->start_time, num);
		pthread_mutex_unlock(&philos->data->mutex.write_flag);
	}
	id = 0;
	while (id < philos->data->args.count_philo)
	{
		pthread_join(philos[id].philo, NULL);
		id++;
	}
}
