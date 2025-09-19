/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgingast <mgingast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:05:46 by mgingast          #+#    #+#             */
/*   Updated: 2025/09/19 17:10:47 by mgingast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ezprompt.h"

bool	is_l(char c, t_prompt *p)
{
	if (c == '\f')
	{
		write(1, "\x1b[2J\x1b[H", 7);
		write(1, p->prompt, ft_strlen(p->prompt));
		write(1, p->input, p->input_size);
		return (true);
	}
	return (false);
}

bool	is_d(char c, t_prompt *p)
{
	if (c == 0x04)
	{
		write(1, "\n", 1);
		write(1, p->prompt, ft_strlen(p->prompt));
		p->exit_flag = 1;
		return (true);
	}
	return (false);
}

bool	is_backspace(char c, t_prompt *p)
{
	if (c == 127 || c == 8)
	{
		if (p->input_size > 0)
		{
			p->input_size--;
			p->input[p->input_size] = '\0';
			write(1, "\b \b", 3);
		}
		return (true);
	}
	return (false);
}

bool	is_empty(char *str)
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

bool	is_skipable(char c, t_prompt *p)
{
	if (c == '\t' || c == 0x1F
		|| is_l(c, p)
		|| is_d(c, p)
		|| is_backspace(c, p))
		return (true);
	return (false);
}
