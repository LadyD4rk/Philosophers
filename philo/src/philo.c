/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:31:42 by jobraga-          #+#    #+#             */
/*   Updated: 2025/09/23 20:11:35 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	is_valid_argument(int ac, char **av)
{
	int		arg;
	int		cha;

	arg = 1;
	while (arg < ac)
	{
		cha = 0;
		while (av[arg][cha])
		{
			if ((!(av[arg][cha] >= '0' && av[arg][cha] <= '9'))
				|| ft_atoi(av[arg]) < 1)
			{
				ft_putstr_fd("Invalid argument", 2);
				return (0);
			}
			cha++;
		}
		arg++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	(void)av;
	if (ac == 5 || ac == 6)
	{
		if (is_valid_argument(ac, av) == 0)
			return (0);
	}
	else
		return (printf("erro"), 1);
	return (0);
}
