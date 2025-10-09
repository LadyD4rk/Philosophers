/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:28:13 by jobraga-          #+#    #+#             */
/*   Updated: 2025/10/09 11:01:52 by jobraga-         ###   ########.fr       */
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
	if (philos)
		free(philos);
	if (mutex->forks)
		free(mutex->forks);
}

void	*routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	printf("Philo %d: teste e teste\n", philo->id);
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
	id = 0;
	while (id < philos->data->args.count_philo)
	{
		pthread_join(philos[id].philo, NULL);
		id++;
	}
}

int	main(int ac, char **av)
{
	t_data		data;

	if (ac == 5 || ac == 6)
	{
		if (is_valid_argument(ac, av) == 0)
			return (1);
		initialize_all(&data, av);
		start_dinner(data.philos);
		//print_philo(data.philos, data.args.count_philo);
		clear_all(data.philos, &data.mutex);
	}
	else
		return (ft_putstr_fd("Invalid number of arguments", 2), 1);
}
