/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ensure_capacity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgingast <mgingast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:48:50 by mgingast          #+#    #+#             */
/*   Updated: 2025/10/16 13:54:16 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "ezprompt.h"

static size_t	calc_new_capacity(size_t current, const size_t needed)
{
	if (current == 0)
		current = 64;
	while (current < needed)
	{
		if (current > SIZE_MAX / 2)
			return (needed);
		current *= 2;
	}
	return (current);
}

bool	ensure_capacity(void **buffer, size_t *capacity, const size_t needed,
			const size_t elem_size)
{
	size_t	new_capacity;
	void	*new_buf;

	if (needed < *capacity)
		return (true);
	if (elem_size != 0 && needed > SIZE_MAX / elem_size)
		return (false);
	new_capacity = calc_new_capacity(*capacity, needed);
	if (elem_size != 0 && new_capacity > SIZE_MAX / elem_size)
		return (false);
	new_buf = resize(*buffer, new_capacity * elem_size);
	if (!new_buf)
		return (false);
	*buffer = new_buf;
	*capacity = new_capacity;
	return (true);
}
