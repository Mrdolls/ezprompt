/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgingast <mgingast <mgingast@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 13:08:40 by mgingast          #+#    #+#             */
/*   Updated: 2025/09/29 16:23:36 by mgingast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ezprompt.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

bool	ft_isalnum(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || (c >= '!' && c <= '/')
		|| (c >= ':' && c <= '@') || (c >= '[' && c <= '`')
		|| (c >= '{' && c <= '~'))
		return (true);
	else
		return (false);
}

void	refresh_prompt(t_prompt *p)
{
	int	max;

	max = 1;
	if ((int)ft_strlen(p->prompt) != prompt_width(p->prompt))
		max = 0;
	write(1, "\033[2K\r", 5);
	write(1, p->prompt, prompt_width(p->prompt) + 1);
	ft_putstr(p->input);
	write(1, "\033[", 2);
	ft_putnbr_fd(prompt_width(p->prompt) + p->cursor_pos + max, 1);
	write(1, "G", 1);
}

void	update_prompt(t_prompt *p, char *new_prompt)
{
	free(p->prompt);
	p->prompt = ft_strdup(new_prompt);
}
