/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:45:00 by jobraga-          #+#    #+#             */
/*   Updated: 2025/10/09 12:31:34 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*ft_calloc(size_t num, size_t tam)
{
	void	*buffer;

	if ((tam != 0 && num != 0) && num > SIZE_MAX / tam)
		return (NULL);
	buffer = malloc(num * tam);
	if (!buffer)
		return (NULL);
	memset(buffer, 0, num * tam);
	return (buffer);
}
