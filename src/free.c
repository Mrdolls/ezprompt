/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgingast <mgingast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:30:35 by mgingast          #+#    #+#             */
/*   Updated: 2025/10/16 17:58:35 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ezprompt.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_prompt(t_prompt *p)
{
	if (p->input)
		free(p->input);
	if (p->prompt)
		free(p->prompt);
	if (p->history.entries)
		free_tab(p->history.entries);
}
