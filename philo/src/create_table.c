/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:32:44 by jobraga-          #+#    #+#             */
/*   Updated: 2025/09/24 16:39:26 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*routine(void *arg)
{
	printf("Existe ID: %ld\n", pthread_self());
	usleep(1000 * 100);
	(void)arg;
	return (NULL);
}

void	inicialize_philo(t_philo *philo)
{
	philo->tm_die = 0;
	philo->tm_eat = 0;
	philo->tm_sleep = 0;
	philo->count_eat = 0;
	philo->die = 0;
}

void	create_table(t_philo *table, int count_philo, char **av)
{
	int		num;

	table = malloc(sizeof(t_philo) * (count_philo + 1));
	if (!table)
		return ;
	num = 1;
	while (num <= count_philo)
	{
		pthread_create(&table[num].philo, NULL, routine, &table[num]);
		inicialize_philo(&table[num]);
		printf("philo: %d tm die: %d tm eat: %d tm sleep: %d count_eat: %d die: %d\n",
			num, table[num].tm_die, table[num].tm_eat, table[num].tm_sleep,
			table[num].count_eat, table[num].die);
		usleep(1000 * 100);
		num++;
	}
	clear_table(table, count_philo);
	(void)av;
}
