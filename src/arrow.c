/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgingast <mgingast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:34:03 by mgingast          #+#    #+#             */
/*   Updated: 2025/09/19 17:10:27 by mgingast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ezprompt.h"

t_arrow	get_arrow(void)
{
	char	c;

	if (read(0, &c, 1) <= 0)
		return (ARROW_NONE);
	if (c != '[')
		return (ARROW_NONE);
	if (read(0, &c, 1) <= 0)
		return (ARROW_NONE);
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

void	set_history_up(t_prompt *p)
{
	if (p->history_size == 0)
		return ;
	if (p->history_index <= 0)
		p->history_index = p->history_size - 1;
	else
		p->history_index--;
	free(p->input);
	p->input = resize(p->history[p->history_index], 64, false);
	if (!p->input)
		return ;
	p->input_size = ft_strlen(p->input);
	write(1, "\x1b[2K\r", 5);
	write(1, p->prompt, ft_strlen(p->prompt));
	write(1, p->input, p->input_size);
}

void	set_history_down(t_prompt *p)
{
	if (p->history_size == 0)
		return ;
	if (p->history_index >= p->history_size - 1)
	{
		p->history_index = p->history_size;
		free(p->input);
		p->input = ft_strdup("");
		if (!p->input)
			return ;
	}
	else
	{
		p->history_index++;
		free(p->input);
		p->input = resize(p->history[p->history_index], 64, false);
		if (!p->input)
			return ;
	}
	p->input_size = ft_strlen(p->input);
	write(1, "\x1b[2K\r", 5);
	write(1, p->prompt, ft_strlen(p->prompt));
	write(1, p->input, p->input_size);
}

bool	play_arrow(t_prompt *p)
{
	t_arrow	arrow;

	arrow = get_arrow();
	if (arrow == ARROW_UP)
		set_history_up(p);
	else if (arrow == ARROW_DOWN)
		set_history_down(p);
	return (true);
}
