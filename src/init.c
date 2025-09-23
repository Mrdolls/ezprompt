/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgingast <mgingast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:31:36 by mgingast          #+#    #+#             */
/*   Updated: 2025/09/23 10:45:49 by mgingast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ezprompt.h"

static void	set_input_mode(void)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

bool	init_prompt(t_prompt **p, char *prompt)
{
	set_input_mode();
	*p = calloc(1, sizeof(t_prompt));
	if (!(*p))
		return (1);
	if (!(*p)->input)
	{
		(*p)->input_capacity = 64;
		(*p)->input = resize((*p)->input, 64, true);
		if (!(*p)->input)
			return (false);
	}
	if (!(*p)->history.entries)
	{
		(*p)->history.capacity = 64;
		(*p)->history.size = 0;
		(*p)->history.entries = calloc(1,
				sizeof(char *) * (*p)->history.capacity);
		if (!(*p)->history.entries)
			return (false);
	}
	(*p)->prompt = ft_strdup(prompt);
	return (true);
}

bool	clear_input(t_prompt *p)
{
	if (p->input)
	{
		free(p->input);
		p->input = ft_strdup(" ");
		p->input = resize(p->input, 64, true);
		if (!p->input)
			return (false);
		p->input_size = 0;
	}
	return (true);
}
