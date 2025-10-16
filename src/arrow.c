/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgingast <mgingast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:34:03 by mgingast          #+#    #+#             */
/*   Updated: 2025/10/16 16:57:26 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "ezprompt.h"
#include "utils.h"

static inline t_arrow	parse_final(unsigned char c)
{
	if (c == 'A')
		return (ARROW_UP);
	if (c == 'B')
		return (ARROW_DOWN);
	if (c == 'C')
		return (ARROW_RIGHT);
	if (c == 'D')
		return (ARROW_LEFT);
	return (ARROW_NONE);
}

t_arrow	get_arrow(void)
{
	unsigned char	c;

	if (read(0, &c, 1) <= 0)
		return (ARROW_NONE);
	if (c == '[')
	{
		if (read(0, &c, 1) <= 0)
			return (ARROW_NONE);
		return (parse_final(c));
	}
	if (c != 0x1B)
		return (ARROW_NONE);
	if (read(0, &c, 1) <= 0)
		return (ARROW_NONE);
	if (c != '[')
		return (ARROW_NONE);
	if (read(0, &c, 1) <= 0)
		return (ARROW_NONE);
	return (parse_final(c));
}

void	set_history_up(t_prompt *p)
{
	if (p->history.size == 0)
		return ;
	if (p->history.index <= 0)
		p->history.index = p->history.size - 1;
	else
		p->history.index--;
	free(p->input);
	p->input = ft_strdup(p->history.entries[p->history.index]);
	if (!p->input)
		return ;
	p->input_size = ft_strlen(p->input);
	write(1, "\x1b[2K\r", 5);
	write(1, p->prompt, ft_strlen(p->prompt));
	write(1, p->input, p->input_size);
	p->cursor_pos = p->input_size;
}

void	set_history_down(t_prompt *p)
{
	if (p->history.size == 0)
		return ;
	if (p->history.index >= p->history.size - 1)
	{
		p->history.index = p->history.size;
		free(p->input);
		p->input = ft_calloc(1, 64);
		if (!p->input)
			return ;
	}
	else
	{
		p->history.index++;
		free(p->input);
		p->input = ft_strdup(p->history.entries[p->history.index]);
		if (!p->input)
			return ;
	}
	p->input_size = ft_strlen(p->input);
	write(1, "\x1b[2K\r", 5);
	write(1, p->prompt, ft_strlen(p->prompt));
	write(1, p->input, p->input_size);
	p->cursor_pos = p->input_size;
}

static inline void	set_cursor(t_prompt *p, t_arrow arrow)
{
	if (arrow == ARROW_LEFT && p->cursor_pos > 0)
	{
		p->cursor_pos--;
		write(1, "\033[D", 3);
	}
	else if (arrow == ARROW_RIGHT && p->cursor_pos < p->input_size)
	{
		p->cursor_pos++;
		write(1, "\033[C", 3);
	}
}

bool	play_arrow(t_prompt *p)
{
	t_arrow	arrow;

	arrow = get_arrow();
	if (arrow == ARROW_UP)
		set_history_up(p);
	else if (arrow == ARROW_DOWN)
		set_history_down(p);
	else if (arrow == ARROW_LEFT)
		set_cursor(p, ARROW_LEFT);
	else if (arrow == ARROW_RIGHT)
		set_cursor(p, ARROW_RIGHT);
	return (true);
}
