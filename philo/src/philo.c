/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:28:13 by jobraga-          #+#    #+#             */
/*   Updated: 2025/11/11 23:28:32 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	initialize_all(t_data *data, char **av)
{
	data->philo_check = 0;
	data->dead_flag = 0;
	data->id_dead = 0;
	data->start_time = ft_get_time();
	initialize_args(&data->args, av);
	if (initialize_mutex(data, &data->mutex))
		return (1);
	data->philos = create_table(data);
	if (!data->philos)
		return (1);
	return (0);
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
		if (ft_atoi(av[1]) == 1)
		{
			printf("0 1 has taken a fork\n");
			ft_usleep(ft_atoi(av[2]));
			printf("%i 1 died\n", ft_atoi(av[2]));
			return (0);
		}
		if (initialize_all(&data, av))
		{
			ft_putstr_fd("ERROR: Failed to initialize arguments", 2);
			clear_all(data.philos, &data.mutex);
			return (1);
		}
		if (data.philo_check == 1)
			start_dinner(data.philos);
		clear_all(data.philos, &data.mutex);
	}
	else
		return (ft_putstr_fd("ERROR: Invalid number of arguments", 2), 1);
}
