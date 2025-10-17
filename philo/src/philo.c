/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:28:13 by jobraga-          #+#    #+#             */
/*   Updated: 2025/10/17 12:37:38 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	print_philo(t_philo *table, int count)
{
	int		i;

	i = 0;
	while (i < count)
	{
		printf("count_eat: %i\n", table[i].data->args.count_eat);
		printf("count_philo: %i\n", table[i].data->args.count_philo);
		printf("time_die: %i\n", table[i].data->args.time_die);
		printf("time_sleep: %i\n", table[i].data->args.time_sleep);
		printf("time_eat: %i\n", table[i].data->args.time_eat);
		printf("id: %i\n", table[i].id);
		printf("last_eat_time: %ld\n", table[i].last_eat_time);
		printf("count_eat: %i\n\n\n", table[i].count_eat);
		i++;
	}
}

void	clear_all(t_philo *philos, t_mutex *mutex)
{
	int		id;

	id = 0;
	if (mutex)
	{
		if (mutex->forks)
		{
			while (id < philos->data->args.count_philo)
			{
				pthread_mutex_destroy(&mutex->forks[id]);
				id++;
			}
		}
		free(mutex->forks);
		if (mutex->init_dead_flag)
			pthread_mutex_destroy(&mutex->dead_flag);
		if (mutex->init_write_flag)
			pthread_mutex_destroy(&mutex->write_flag);
		if (mutex->init_meal_flag)
			pthread_mutex_destroy(&mutex->meal_flag);
	}
	if (philos)
		free(philos);
}

int	main(int ac, char **av)
{
	t_data		data;

	if (ac == 5 || ac == 6)
	{
		if (is_valid_argument(ac, av) == 0)
			return (1);
		if (initialize_all(&data, av))
		{
			ft_putstr_fd("ERROR: failed to initialize arguments", 2);
			clear_all(data.philos, &data.mutex);
			return (1);
		}
		if (data.philo_check == 1)
			start_dinner(data.philos);
		//print_philo(data.philos, data.args.count_philo);
		clear_all(data.philos, &data.mutex);
	}
	else
		return (ft_putstr_fd("Invalid number of arguments", 2), 1);
}
