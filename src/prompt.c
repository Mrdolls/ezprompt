/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:57:50 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/10/16 19:31:47 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "ezprompt.h"
#include "core/string/ft_string.h"
#include "io/ft_printf.h"

void	refresh_prompt(const t_prompt *p)
{
	size_t	max;

	max = 1;
	if (ft_strlen(p->prompt) != prompt_width(p->prompt))
		max = 0;
	ft_printf("\033[2K\r");
	write(1, p->prompt, prompt_width(p->prompt) + 1);
	ft_printf("%s\033[ %zuG", p->input,
		(prompt_width(p->prompt) + p->cursor_pos + max));
}

void	update_prompt(t_prompt *p, const char *new_prompt)
{
	free(p->prompt);
	p->prompt = ft_strdup(new_prompt);
}
