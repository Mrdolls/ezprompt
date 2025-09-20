/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgingast <mgingast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:23:02 by mgingast          #+#    #+#             */
/*   Updated: 2025/09/20 19:11:43 by mgingast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ezprompt.h"

static bool	append_char(t_prompt *p, char c)
{
	write(1, &c, 1);
	if (!ensure_capacity((void **)&p->input, &p->input_capacity,
			p->input_size + 2, sizeof(char)))
		return (false);
	p->input[p->input_size++] = c;
	p->input[p->input_size] = '\0';
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
