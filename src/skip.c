/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgingast <mgingast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:05:46 by mgingast          #+#    #+#             */
/*   Updated: 2025/10/16 19:15:11 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ezprompt.h"
#include "core/string/ft_string.h"

bool	is_l(const char c, t_prompt *p)
{
	if (c == '\f')
	{
		write(1, "\x1b[2J\x1b[H", 7);
		write(1, p->prompt, ft_strlen(p->prompt));
		write(1, p->input, p->input_size);
		p->cursor_pos = p->input_size;
		return (true);
	}
	return (false);
}

bool	is_d(const char c, t_prompt *p)
{
	if (c == 0x04)
	{
		write(1, "\n", 1);
		p->exit_flag = 1;
		return (true);
	}
	return (false);
}

bool	is_backspace(const char c, t_prompt *p)
{
	if (c == 127 || c == 8)
	{
		if (p->input_size > 0)
		{
			p->input = delete_char(p->input, &p->cursor_pos, &p->input_size);
			refresh_prompt(p);
		}
		return (true);
	}
	return (false);
}

bool	is_empty(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (true);
	while (str[i])
	{
		if (str[i] != ' ' && !(str[i] >= 9 && str[i] <= 13))
			return (false);
		i++;
	}
	return (true);
}

bool	is_skipable(const char c, t_prompt *p)
{
	if (c == '\t' || c == 0x1F
		|| is_l(c, p)
		|| is_d(c, p)
		|| is_backspace(c, p))
		return (true);
	return (false);
}
