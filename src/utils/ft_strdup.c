/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgingast <mgingast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:46:04 by mgingast          #+#    #+#             */
/*   Updated: 2025/10/16 13:04:41 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "utils.h"

char	*ft_strdup(const char *str)
{
	size_t	size;
	size_t	i;
	char	*temp;

	if (!str)
		return (NULL);
	size = ft_strlen(str);
	temp = ft_calloc(1, sizeof(char) * size + 1);
	if (temp == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		temp[i] = str[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
