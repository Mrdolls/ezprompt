/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:35:49 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/10/16 13:34:23 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#include "ezprompt.h"

static size_t	char_display_width(const char *s)
{
	unsigned char	c;

	c = (unsigned char)*s;
	if (c < 0x80)
		return (1);
	if ((c & 0xE0) == 0xC0)
		return (2);
	if ((c & 0xF0) == 0xE0)
		return (2);
	if ((c & 0xF8) == 0xF0)
		return (2);
	return (1);
}

size_t	prompt_width(const char *s)
{
	size_t	width;
	size_t	i;
	size_t	w;

	width = 0;
	i = 0;
	while (s[i])
	{
		w = char_display_width(&s[i]);
		width += w;
		if ((s[i] & 0xE0) == 0xC0)
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
