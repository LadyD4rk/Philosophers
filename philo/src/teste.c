/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:51:14 by jobraga-          #+#    #+#             */
/*   Updated: 2025/09/23 20:10:39 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*thread_function(void *arg)
{
	int		i;

	i = 1;
	while (i <= 10)
	{
		printf("Thread ID: %ld, Número: %d\n", pthread_self(), i);
		usleep(1000 * 1000);
		i++;
	}
	(void)arg;
	return (NULL);
}

int	teste(void)
{
	pthread_t	thread1;
	pthread_t	thread2;

	pthread_create(&thread1, NULL, thread_function, NULL);
	pthread_create(&thread2, NULL, thread_function, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("Threads finalizadas.\n");
	return (0);
}
