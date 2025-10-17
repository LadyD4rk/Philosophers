/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:51:48 by jobraga-          #+#    #+#             */
/*   Updated: 2025/10/17 13:47:47 by jobraga-         ###   ########.fr       */
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

int	initialize_mutex2(t_mutex *mutex)
{
	mutex->init_write_flag = 0;
	mutex->init_dead_flag = 0;
	mutex->init_meal_flag = 0;
	if (pthread_mutex_init(&mutex->write_flag, NULL) != 0)
		return (1);
	else
		mutex->init_write_flag = 1;
	if (pthread_mutex_init(&mutex->dead_flag, NULL) != 0)
		return (1);
	else
		mutex->init_dead_flag = 1;
	if (pthread_mutex_init(&mutex->meal_flag, NULL) != 0)
		return (1);
	else
		mutex->init_meal_flag = 0;
	return (0);
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
		if (pthread_mutex_init(&mutex->forks[fork], NULL) != 0)
		{
			while (--fork >= 0)
				pthread_mutex_destroy(&mutex->forks[fork]);
			return (1);
		}
		fork++;
	}
	if (initialize_mutex2(mutex))
		return (1);
	return (0);
}

static void	initialize_philo(t_philo *philo, int id, t_data *data)
{
	philo->data = data;
	philo->last_eat_time = ft_get_time();
	philo->start_time = ft_get_time();
	philo->id = id + 1;
	philo->count_eat = 0;
	philo->limit_eat = 0;
	philo->l_fork = &data->mutex.forks[id];
	philo->r_fork = &data->mutex.forks[(id + 1) % data->args.count_philo];
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
	if (philo == data->args.count_philo)
		data->philo_check = 1;
	return (table);
}

int	initialize_all(t_data *data, char **av)
{
	data->philo_check = 0;
	data->dead_flag = 0;
	initialize_args(&data->args, av);
	if (initialize_mutex(data, &data->mutex))
		return (1);
	data->philos = create_table(data);
	if (!data->philos)
		return (1);
	return (0);
}
