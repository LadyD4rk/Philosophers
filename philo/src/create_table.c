/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:32:44 by jobraga-          #+#    #+#             */
/*   Updated: 2025/09/28 14:23:16 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	inicialize_philo(t_philo *philo, t_time time, int id)
{
	philo->id = id + 1;
	philo->tm_die = 0;
	philo->tm_eat = 0;
	philo->tm_sleep = 0;
	philo->count_eat = 0;
	philo->die = 0;
	philo->last_eat = ft_get_time();
	philo->time = time;
}

void	create_table(t_data *data, t_time time, int count_philo)
{
	int		num;

	data->table = malloc(sizeof(t_philo) * (count_philo + 1));
	if (!data->table)
		return ;
	num = 0;
	while (num < count_philo)
	{
		inicialize_philo(&data->table[num], time, num);
		num++;
	}
}
