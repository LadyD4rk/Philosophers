/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_argument.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 10:36:28 by jobraga-          #+#    #+#             */
/*   Updated: 2025/09/24 10:36:53 by jobraga-         ###   ########.fr       */
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
