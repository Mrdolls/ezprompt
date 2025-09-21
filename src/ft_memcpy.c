/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpyc                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgingast <mgingast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:25:31 by mgingast          #+#    #+#             */
/*   Updated: 2025/04/26 21:25:31 by mgingast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ezprompt.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	void	*temp;

	i = 0;
	if (!dest && !src)
		return (NULL);
	temp = (char *)dest;
	while (i < n)
	{
		*(char *)temp = *(char *)src;
		temp++;
		src++;
		i++;
	}
	return (dest);
}
