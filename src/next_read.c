/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgingast <mgingast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:23:02 by mgingast          #+#    #+#             */
/*   Updated: 2025/09/24 12:53:04 by mgingast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ezprompt.h"

static bool	append_char(t_prompt *p, char c)
{
	char	*new_input;

	if (!ensure_capacity((void **)&p->input, &p->input_capacity,
			p->input_size + 2, sizeof(char)))
		return (false);
	new_input = insert_char(p->input, c, p->cursor_pos);
	if (!new_input)
		return (false);
	p->input = new_input;
	p->input_size++;
	p->cursor_pos++;
	refresh_prompt(p);
	return (true);
}

static bool	set_history(t_prompt *p)
{
	if (is_empty(p->input) || (p->history.size > 0 && ft_strncmp(p->input,
				p->history.entries[p->history.size - 1],
				ft_strlen(p->input)) == 0))
	{
		p->history.index = p->history.size;
		return (true);
	}
	if (!ensure_capacity((void **)&p->history.entries, &p->history.capacity,
			p->history.size + 1, sizeof(char*)))
		return (false);
	p->history.entries[p->history.size] = ft_strdup(p->input);
	if (!p->history.entries[p->history.size])
		return (false);
	p->history.size++;
	p->history.index = p->history.size;
	return (true);
}

static bool	get_input(t_prompt *p)
{
	char	c;
	int		len;

	len = 1;
	while (len)
	{
		len = read(0, &c, 1);
		if (len == -1 || is_d(c, p))
			return (false);
		if (c == '\n')
			return (write(1, &c, 1), true);
		if (c == 27)
		{
			if (!play_arrow(p))
				return (false);
			continue ;
		}
		if (is_skipable(c, p))
			continue ;
		if (!append_char(p, c))
			return (false);
	}
	return (true);
}

bool	next_read(t_prompt *p)
{
	p->cursor_pos = 0;
	write(1, p->prompt, ft_strlen(p->prompt));
	if (!get_input(p))
		return (false);
	clear_extra_space(p);
	if (!set_history(p))
		return (false);
	return (true);
}
