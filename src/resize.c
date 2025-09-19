/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgingast <mgingast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:36:55 by mgingast          #+#    #+#             */
/*   Updated: 2025/09/19 17:02:14 by mgingast         ###   ########.fr       */
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
