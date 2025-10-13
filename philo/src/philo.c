/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:28:13 by jobraga-          #+#    #+#             */
/*   Updated: 2025/10/13 15:48:56 by jobraga-         ###   ########.fr       */
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
	if (philos->data->waiter)
		pthread_join(philos->data->waiter, NULL);
	if (mutex)
	{
		free(mutex->forks);
		pthread_mutex_destroy(&mutex->dead_flag);
		pthread_mutex_destroy(&mutex->write_flag);
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
		initialize_all(&data, av);
		start_dinner(data.philos);
		//print_philo(data.philos, data.args.count_philo);
		clear_all(data.philos, &data.mutex);
	}
	else
		return (ft_putstr_fd("Invalid number of arguments", 2), 1);
}
