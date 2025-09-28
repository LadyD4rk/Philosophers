/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:31:42 by jobraga-          #+#    #+#             */
/*   Updated: 2025/09/26 12:39:41 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	clear_table(t_philo *table, int count_philo)
{
	int		num;

	num = 1;
	while (num <= count_philo)
	{
		pthread_join(table[num].philo, NULL);
		num++;
	}
	free(table);
}

void	clock_(t_time *time)
{
	printf("\n\nTIME\n");
	printf("Start time: %ld\n", time->start_time);
	printf("Time eat: %d\n", time->time_eat);
	printf("Time die: %d\n", time->time_die);
	printf("Time sleep: %d\n", time->time_sleep);
}

int	main(int ac, char **av)
{
	static t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (is_valid_argument(ac, av) == 0)
			return (0);
		create_time(&data.time, av);
		create_table(data.table, data.time, ft_atoi(av[1]), av);
		//clock_(&data.time);
	}
	else
		return (ft_putstr_fd("Invalid number of arguments", 2), 1);
	return (0);
}
