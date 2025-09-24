/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:31:42 by jobraga-          #+#    #+#             */
/*   Updated: 2025/09/24 16:03:48 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*routine(void *arg)
{
	printf("Existe ID: %ld\n", pthread_self());
	usleep(1000 * 100);
	(void)arg;
	return(NULL);
}

void	create_table(t_philo *table, int count_philo, char **av)
{
	int		num;
	
	table = malloc(sizeof(t_philo) * (count_philo + 1));
	if (!table)
		return ;
	num = 0;
	while (num <= count_philo)
	{
		pthread_create(&table[num].philo, NULL, routine, &table[num]);
		printf("tm die: %i tm eat: %i tm sleep: %i count_eat: %i die: %i\n", 
			table[num].tm_die, table[num].tm_eat, table[num].tm_sleep, 
			table[num].count_eat, table[num].die);
		usleep(1000 * 100);
		num++;
	}
	num = 0;
	while (num <= count_philo)
	{
		pthread_join(table[num].philo, NULL);
		num++;
	}
	(void)av;
}

int	main(int ac, char **av)
{
	static t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (is_valid_argument(ac, av) == 0)
			return (0);
		create_table(data.table, ft_atoi(av[1]), av);
	}
	else
		return (ft_putstr_fd("Invalid number of arguments", 2), 1);
	return (0);
}
