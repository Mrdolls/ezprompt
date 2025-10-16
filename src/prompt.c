/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:57:50 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/10/16 13:32:35 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "ezprompt.h"
#include "utils.h"

void	refresh_prompt(const t_prompt *p)
{
	size_t	max;

	max = 1;
	if (ft_strlen(p->prompt) != prompt_width(p->prompt))
		max = 0;
	write(1, "\033[2K\r", 5);
	write(1, p->prompt, prompt_width(p->prompt) + 1);
	ft_putstr(p->input);
	write(1, "\033[", 2);
	ft_putnbr_fd((int)(prompt_width(p->prompt) + p->cursor_pos + max), 1);
	write(1, "G", 1);
}

void	update_prompt(t_prompt *p, const char *new_prompt)
{
	free(p->prompt);
	p->prompt = ft_strdup(new_prompt);
}
