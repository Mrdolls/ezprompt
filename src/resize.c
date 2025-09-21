/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgingast <mgingast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:36:55 by mgingast          #+#    #+#             */
/*   Updated: 2025/09/21 16:19:14 by mgingast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ezprompt.h"

char	*resize(char *old, int n, bool free_old)
{
	int		i;
	char	*new;

	if (!old)
	{
		old = malloc(1);
		if (!old)
			return (NULL);
		old[0] = '\0';
	}
	if (n <= 0)
		return (old);
	i = 0;
	new = calloc(1, ft_strlen(old) + n + 1);
	if (!new)
		return (NULL);
	while (old[i])
	{
		new[i] = old[i];
		i++;
	}
	new[i] = '\0';
	if (free_old)
		free(old);
	return (new);
}

char	*insert_char(char *old, char c, int pos)
{
	int		len;
	char	*new;

	if (!old)
		return (NULL);
	len = ft_strlen(old);
	if (pos < 0 || pos > len)
		return (NULL);
	new = calloc(1, ft_strlen(old) + 2);
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
	int		len;
	char	*new;
	int		i;

	if (!old || *cursor_pos <= 0)
		return (old);
	len = ft_strlen(old);
	new = calloc(1, len);
	if (!new)
		return (NULL);
	ft_memcpy(new, old, *cursor_pos - 1);
	ft_memcpy(new + *cursor_pos - 1, old + *cursor_pos, len - *cursor_pos + 1);
	free(old);
	(*cursor_pos)--;
	(*input_size)--;
	return (new);
}
