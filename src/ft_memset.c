/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgingast <mgingast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:28:19 by mgingast          #+#    #+#             */
/*   Updated: 2025/09/19 15:19:30 by mgingast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ezprompt.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s2;
	int				i;

	i = -1;
	s2 = s;
	while ((size_t)i++ != n - 1)
		s2[i] = (unsigned char)c;
	return (s);
}
