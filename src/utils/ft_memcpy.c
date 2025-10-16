/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpyc                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgingast <mgingast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:25:31 by mgingast          #+#    #+#             */
/*   Updated: 2025/10/16 16:49:17 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_memcpy(void *dest, const void *src, const size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;
	size_t				i;

	if (n == 0)
		return (dest);
	if (!dest || !src)
		return (dest);
	s = (const unsigned char *)src;
	d = (unsigned char *)dest;
	if (d == s)
		return (dest);
	if (d > s && d < s + n)
	{
		i = n;
		while (i-- > 0)
			d[i] = s[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}
