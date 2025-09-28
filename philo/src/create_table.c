/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:32:44 by jobraga-          #+#    #+#             */
/*   Updated: 2025/09/28 11:25:32 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*routine(void *arg)
{
	int		i;
	t_philo	*philo;
	t_time	time;

	i = 1;
	philo = (t_philo *)arg;
	time = philo->time;
	while (ft_get_time() - philo->last_eat < time.time_die)
	{
		philo->count_eat++;
		printf("O philo %i está vivo. Comeu %i vezes. \n", philo->id, philo->count_eat);
		usleep(i * 50 * 1000);
		philo->tm_eat = ft_get_time();
		i++;
	}
	(void)arg;
	(void)time;
	return (NULL);
}

void	inicialize_philo(t_philo *philo, t_time time, int id)
{
	philo->id = id;
	philo->tm_die = 0;
	philo->tm_eat = 0;
	philo->tm_sleep = 0;
	philo->count_eat = 0;
	philo->die = 0;
	philo->last_eat = ft_get_time();
	philo->time = time;
}

int	ft_check_eat(t_philo *table, int count_philo)
{
	int		i;
	int		philo;
	int		eat;

	i = 1;
	philo = i;
	eat = table[i].count_eat;
	while(i <= count_philo)
	{
		if (table[i].count_eat > eat)
		{
			philo = i;
			eat = table[i].count_eat;
		}
		i++;
	}
	return (philo);
}

void	create_table(t_philo *table, t_time time, int count_philo, char **av)
{
	int		num;

	table = malloc(sizeof(t_philo) * (count_philo + 1));
	if (!table)
		return ;
	num = 1;
	while (num <= count_philo)
	{
		inicialize_philo(&table[num], time, num);
		pthread_create(&table[num].philo, NULL, routine, &table[num]);
/* 		printf("philo: %d tm die: %d tm eat: %d tm sleep: %d count_eat: %d die: %d\n",
			num, table[num].tm_die, table[num].tm_eat, table[num].tm_sleep,
			table[num].count_eat, table[num].die); */
		//clock_(&table[num].time);
		usleep(1000 * 100);
		num++;
	}
	clear_table(table, count_philo);
	(void)av;
}
