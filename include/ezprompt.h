/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ezprompt.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:35:49 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/10/16 16:40:13 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ezprompt.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgingast <mgingast <mgingast@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:23:08 by mgingast          #+#    #+#             */
/*   Updated: 2025/09/29 15:59:08 by mgingast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EZPROMPT_H
# define EZPROMPT_H

# include <stdbool.h>
# include <stddef.h>

typedef struct s_history
{
	char	**entries;
	size_t	size;
	size_t	capacity;
	size_t	index;
}		t_history;

typedef struct s_prompt
{
	char		*prompt;
	char		*input;
	size_t		input_size;
	size_t		input_capacity;
	t_history	history;
	size_t		cursor_pos;
	int			exit_flag;
	char		padding[4];
}			t_prompt;

typedef enum e_arrow
{
	ARROW_NONE,
	ARROW_UP,
	ARROW_DOWN,
	ARROW_LEFT,
	ARROW_RIGHT
}		t_arrow;

// core functions
bool	next_read(t_prompt *p);
void	set_history_up(t_prompt *p);
void	set_history_down(t_prompt *p);
t_arrow	get_arrow(void);
size_t	prompt_width(const char *s);
bool	play_arrow(t_prompt *p);
char	*resize(char *old, size_t n);
char	*insert_char(char *old, char c, size_t pos);
char	*delete_char(char *old, size_t *cursor_pos, size_t *input_size);
void	clear_extra_space(t_prompt *p);
void	refresh_prompt(const t_prompt *p);
void	update_prompt(t_prompt *p, const char *new_prompt);
bool	is_l(char c, t_prompt *p);
bool	is_d(char c, t_prompt *p);
bool	is_backspace(char c, t_prompt *p);
bool	is_empty(const char *str);
bool	is_skipable(char c, t_prompt *p);
void	free_tab(char **tab);
void	free_prompt(t_prompt *p);
bool	init_prompt(t_prompt *p, const char *prompt);
bool	clear_input(t_prompt *p);
bool	ensure_capacity(void **buffer, size_t *capacity,
			size_t needed, size_t elem_size);

#endif
