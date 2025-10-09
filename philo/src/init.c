/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:51:48 by jobraga-          #+#    #+#             */
/*   Updated: 2025/10/09 15:57:16 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	initialize_args(t_args *args, char **av)
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

static int	initialize_mutex(t_data *data, t_mutex *mutex)
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
	//pthread_mutex_lock(&mutex->dead_flag);
	mutex->init = 1;
	return (0);
}

static void	initialize_philo(t_philo *philo, int id, t_data *data)
{
	philo->data = data;
	philo->last_eat_time = ft_get_time();
	philo->start_time = ft_get_time();
	philo->id = id + 1;
	philo->count_eat = 0;
	philo->l_fork = &data->mutex.forks[id];
	philo->r_fork = &data->mutex.forks[id % (data->args.count_philo - 1)];
}

static t_philo	*create_table(t_data *data)
{
	int		philo;
	t_philo	*table;

	table = ft_calloc(data->args.count_philo, sizeof(t_philo));
	if (!table)
		return (NULL);
	philo = 0;
	while (philo < data->args.count_philo)
	{
		initialize_philo(&table[philo], philo, data);
		philo++;
	}
	return (table);
}

void 	initialize_all(t_data *data, char **av)
{
	initialize_args(&data->args, av);
	initialize_mutex(data, &data->mutex);
	data->philos = create_table(data);
}
