/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:31:42 by jobraga-          #+#    #+#             */
/*   Updated: 2025/09/28 14:33:52 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	clear_table(t_philo *table, int count_philo)
{
	int		num;

	num = 0;
	while (num < count_philo)
	{
		pthread_join(table[num].philo, NULL);
		num++;
	}
	free(table);
}

int	main(int ac, char **av)
{
	static t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (is_valid_argument(ac, av) == 0)
			return (0);
		create_time(&data.time, av);
		create_table(&data, data.time, ft_atoi(av[1]));
		if (data.table)
			thread_create(&data, ft_atoi(av[1]));
	}
	else
		return (ft_putstr_fd("Invalid number of arguments", 2), 1);
	return (0);
}
