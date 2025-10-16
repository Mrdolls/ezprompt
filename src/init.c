/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgingast <mgingast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:31:36 by mgingast          #+#    #+#             */
/*   Updated: 2025/10/16 13:53:59 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "ezprompt.h"
#include "utils.h"

static void	set_input_mode(void)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= (tcflag_t) ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

bool	init_prompt(t_prompt *p, const char *prompt)
{
	set_input_mode();
	p = ft_calloc(1, sizeof(t_prompt));
	if (!p)
		return (false);
	if (!p->input)
	{
		p->input_capacity = 64;
		p->input = resize(p->input, 64);
		if (!p->input)
			return (false);
	}
	if (!p->history.entries)
	{
		p->history.capacity = 64;
		p->history.size = 0;
		p->history.entries = ft_calloc(1,
				sizeof(char *) * p->history.capacity);
		if (!p->history.entries)
			return (false);
	}
	p->prompt = ft_strdup(prompt);
	p->exit_flag = true;
	return (true);
}

bool	clear_input(t_prompt *p)
{
	if (p->input)
	{
		free(p->input);
		p->input = ft_strdup(" ");
		p->input = resize(p->input, 64);
		if (!p->input)
			return (false);
		p->input_size = 0;
	}
	return (true);
}
