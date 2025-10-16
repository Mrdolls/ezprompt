/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgingast <mgingast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:31:36 by mgingast          #+#    #+#             */
/*   Updated: 2025/10/16 17:19:16 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "ezprompt.h"
#include "utils.h"

static void	init_prompt_fields(t_prompt *p)
{
	p->input = NULL;
	p->input_size = 0;
	p->input_capacity = 0;
	p->history.entries = NULL;
	p->history.size = 0;
	p->history.capacity = 0;
	p->cursor_pos = 0;
	p->exit_flag = false;
	p->prompt = NULL;
}

static void	set_input_mode(void)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= (tcflag_t) ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

static inline bool	fail_and_free_prompt(t_prompt *prompt)
{
	free_prompt(prompt);
	return (false);
}

bool	init_prompt(t_prompt *p, const char *prompt)
{
	set_input_mode();
	p = ft_calloc(1, sizeof(t_prompt));
	if (!p)
		return (false);
	init_prompt_fields(p);
	p->input_capacity = 512;
	p->input = ft_calloc(p->input_capacity, sizeof(char));
	if (!p->input)
		return (fail_and_free_prompt(p));
	if (prompt)
	{
		p->prompt = ft_strdup(prompt);
		if (!p->prompt)
			return (fail_and_free_prompt(p));
	}
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
