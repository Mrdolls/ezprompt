/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgingast <mgingast <mgingast@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:20:42 by mgingast          #+#    #+#             */
/*   Updated: 2025/09/29 16:24:19 by mgingast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ezprompt.h"

static int	char_display_width(const char *s)
{
	unsigned char	c;

	c = (unsigned char)*s;
	if (c < 0x80)
		return (1);
	if ((c & 0xE0) == 0xC0)
		return (2);
	else if ((c & 0xF0) == 0xE0)
		return (2);
	if ((c & 0xF8) == 0xF0)
		return (2);
	return (1);
}

int	prompt_width(const char *s)
{
	int	width;
	int	i;
	int	w;

	width = 0;
	i = 0;
	while (s[i])
	{
		w = char_display_width(&s[i]);
		width += w;
		if ((unsigned char)s[i] < 0x80)
			i += 1;
		else if ((s[i] & 0xE0) == 0xC0)
			i += 2;
		else if ((s[i] & 0xF0) == 0xE0)
			i += 3;
		else if ((s[i] & 0xF8) == 0xF0)
			i += 4;
		else
			i += 1;
	}
	return (width);
}
