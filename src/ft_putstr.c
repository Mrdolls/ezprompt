/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgingast <mgingast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 13:08:40 by mgingast          #+#    #+#             */
/*   Updated: 2025/09/21 13:33:40 by mgingast         ###   ########.fr       */
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

void	refresh_prompt(t_prompt *p)
{
	write(1, "\033[2K\r", 5);
	ft_putstr(p->prompt);
	ft_putstr(p->input);
	write(1, "\033[", 2);
	ft_putnbr_fd((int)ft_strlen(p->prompt) + p->cursor_pos + 1, 1);
	write(1, "G", 1);
}
