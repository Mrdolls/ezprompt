/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgingast <mgingast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:23:02 by mgingast          #+#    #+#             */
/*   Updated: 2025/09/20 13:50:16 by mgingast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ezprompt.h"

static bool	append_char(t_prompt *p, char c)
{
	write(1, &c, 1);
	if (p->input_size + 2 >= p->input_capacity)
	{
		p->input = resize(p->input, 64, true);
		if (!p->input)
			return (false);
		p->input_capacity += 64;
	}
	p->input[p->input_size++] = c;
	p->input[p->input_size] = '\0';
	return (true);
}

void	set_history(t_prompt *p)
{
	int		i;
	char	**new_hist;

	if (is_empty(p->input) || (p->history_size > 0 && ft_strncmp(p->input,
				p->history[p->history_size - 1],
				ft_strlen(p->input)) == 0))
		return ;
	if (p->history_size >= p->max_history)
	{
		new_hist = malloc(sizeof(char *) * (p->max_history + 64));
		if (!new_hist)
			return ;
		i = -1;
		while (++i < p->history_size)
			new_hist[i] = p->history[i];
		free(p->history);
		p->history = new_hist;
		p->max_history += 64;
	}
	p->history[p->history_size] = ft_strdup(p->input);
	if (!p->history[p->history_size])
		return ;
	p->history_size++;
	p->history_index = p->history_size;
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

// int	main(void)
// {
// 	int	i;
// 	t_prompt	*p;

// 	p = calloc(1, sizeof(t_prompt));
// 	init_prompt(p, "test> ");
// 	i = 0;
// 	while (i < 2)
// 	{
// 		next_read(p);
// 		clear_input(p);
// 		i++;
// 	}
// 	free_prompt(p);
// 	return (0);
// }
