/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgingast <mgingast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:36:55 by mgingast          #+#    #+#             */
/*   Updated: 2025/10/16 14:00:23 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ezprompt.h"
#include "utils.h"

static inline char	*check_ptr(char *old)
{
	if (!old)
	{
		old = malloc(1);
		if (!old)
			return (NULL);
		old[0] = '\0';
	}
	return (old);
}

char	*resize(char *old, const size_t n)
{
	size_t	i;
	char	*new;

	old = check_ptr(old);
	if (!old)
		return (NULL);
	if (n <= 0)
		return (old);
	i = 0;
	new = ft_calloc(1, ft_strlen(old) + n + 1);
	if (!new)
	{
		free(old);
		return (NULL);
	}
	while (old[i])
	{
		new[i] = old[i];
		i++;
	}
	new[i] = '\0';
	free(old);
	return (new);
}

char	*insert_char(char *old, const char c, const size_t pos)
{
	size_t	len;
	char	*new;

	if (!old)
		return (NULL);
	len = ft_strlen(old);
	if (pos > len)
		return (NULL);
	new = ft_calloc(1, ft_strlen(old) + 2);
	if (!new)
		return (NULL);
	ft_memcpy(new, old, pos);
	new[pos] = c;
	ft_memcpy(new + pos + 1, old + pos, len - pos + 1);
	free(old);
	return (new);
}

char	*delete_char(char *old, size_t *cursor_pos, size_t *input_size)
{
	size_t	len;
	char	*new;

	if (!old || *cursor_pos <= 0)
		return (old);
	len = ft_strlen(old);
	new = ft_calloc(1, len);
	if (!new)
		return (NULL);
	ft_memcpy(new, old, *cursor_pos - 1);
	ft_memcpy(new + *cursor_pos - 1, old + *cursor_pos, len - *cursor_pos + 1);
	free(old);
	(*cursor_pos)--;
	(*input_size)--;
	return (new);
}

void	clear_extra_space(t_prompt *p)
{
	while (!is_empty(p->input) && !ft_isalnum(p->input[p->input_size]))
	{
		p->input[p->input_size] = '\0';
		p->input_size--;
	}
	if (!is_empty(p->input))
		p->input_size++;
}
