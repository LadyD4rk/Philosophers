/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:51:48 by jobraga-          #+#    #+#             */
/*   Updated: 2025/10/08 13:01:48 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	inicialize_args(t_args *args, char **av)
{
	if (av[5])
		args->count_eat = ft_atoi(av[5]);
	else
		args->count_eat = -1;
	args->count_philo = ft_atoi(av[1]);
	args->time_die = ft_atoi(av[2]);
	args->time_sleep = ft_atoi(av[3]);
	args->time_eat = ft_atoi(av[4]);
}

int	inicialize_mutex(t_data *data, t_mutex *mutex)
{
	int		fork;

	mutex->forks = malloc(sizeof(pthread_mutex_t) * data->args.count_philo);
	if (!mutex->forks)
		return (1);
	fork = 0;
	while (fork < data->args.count_philo)
	{
		pthread_mutex_init(&mutex->forks[fork], NULL);
		fork++;
	}
	pthread_mutex_init(&mutex->write_flag, NULL);
	pthread_mutex_init(&mutex->dead_flag, NULL);
	mutex->init = 1;
	return (0);
}

t_philo	*create_table(t_data *data)
{
	int		philo;
	t_philo	*table;

	table = ft_calloc(data->args.count_philo, sizeof(t_philo));
	if (!table)
		return (NULL);
	philo = 0;
	while (philo < data->args.count_philo)
	{
		inicialize_philo(&table[philo], philo, data);
		philo++;
	}
	return (table);
}
