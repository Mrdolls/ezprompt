/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgingast <mgingast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:23:02 by mgingast          #+#    #+#             */
/*   Updated: 2025/09/21 13:26:34 by mgingast         ###   ########.fr       */
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

void	set_history(t_prompt *p)
{
	int		i;
	char	**new_hist;

	if (is_empty(p->input) || (p->history.size > 0 && ft_strncmp(p->input,
				p->history.entries[p->history.size - 1],
				ft_strlen(p->input)) == 0))
		return ;
	if (!ensure_capacity((void **)&p->history.entries, &p->history.capacity,
			p->history.size + 1, sizeof(char*)))
		return ;
	p->history.entries[p->history.size] = ft_strdup(p->input);
	if (!p->history.entries[p->history.size])
		return ;
	p->history.size++;
	p->history.index = p->history.size;
}

bool	next_read(t_prompt *p)
{
	char	c;
	int		len;

	len = 1;
	p->cursor_pos = 0;
	write(1, p->prompt, ft_strlen(p->prompt));
	while (len)
	{
		len = read(0, &c, 1);
		if (len == -1 || is_d(c, p))
			return (false);
		if (c == '\n')
			return (set_history(p), write(1, &c, 1), true);
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
