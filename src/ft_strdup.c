/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgingast <mgingast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:46:04 by mgingast          #+#    #+#             */
/*   Updated: 2025/04/25 20:46:04 by mgingast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ezprompt.h"

char	*ft_strdup(const char *str)
{
	int		size;
	int		i;
	char	*temp;

	i = 0;
	size = ft_strlen(str);
	temp = calloc(1, sizeof(char) * size + 1);
	if (temp == NULL)
		return (NULL);
	while (str[i])
	{
		temp[i] = str[i];
		i++;
	}
	temp[i] = 0;
	return (temp);
}
