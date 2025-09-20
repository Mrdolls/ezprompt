/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ensure_capacity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgingast <mgingast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:48:50 by mgingast          #+#    #+#             */
/*   Updated: 2025/09/20 18:57:06 by mgingast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ezprompt.h"

bool	ensure_capacity(void **buffer, size_t *capacity,
		size_t needed, size_t elem_size)
{
	size_t	new_capacity;
	void	*new_buf;

	if (needed < *capacity)
		return (true);
	if (*capacity == 0)
		new_capacity = 64;
	else
		new_capacity = *capacity * 2;
	while (new_capacity < needed)
		new_capacity *= 2;
	new_buf = resize(*buffer, new_capacity * elem_size, true);
	if (new_buf == NULL)
		return (false);
	*buffer = new_buf;
	*capacity = new_capacity;
	return (true);
}
