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
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <termios.h>
# include <stdio.h>

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
}			t_prompt;

typedef enum e_arrow
{
	ARROW_NONE,
	ARROW_UP,
	ARROW_DOWN,
	ARROW_LEFT,
	ARROW_RIGHT
}		t_arrow;

/*42 functions*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str);
void	ft_putstr(char *str);
bool	ft_isalnum(char c);
void	ft_putnbr_fd(int n, int fd);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);

/*core functions*/
bool	next_read(t_prompt *p);
void	set_history_up(t_prompt *p);
void	set_history_down(t_prompt *p);
t_arrow	get_arrow(void);
int		prompt_width(const char *s);
bool	play_arrow(t_prompt *p);
char	*resize(char *old, int n, bool free_old);
char	*insert_char(char *old, char c, int pos);
char	*delete_char(char *old, size_t *cursor_pos, size_t *input_size);
void	clear_extra_space(t_prompt *p);
void	refresh_prompt(t_prompt *p);
void	update_prompt(t_prompt *p, char *new_prompt);
bool	is_l(char c, t_prompt *p);
bool	is_d(char c, t_prompt *p);
bool	is_backspace(char c, t_prompt *p);
bool	is_empty(char *str);
bool	is_skipable(char c, t_prompt *p);
void	free_tab(char **tab);
void	free_prompt(t_prompt *p);
bool	init_prompt(t_prompt **p, char *prompt);
bool	clear_input(t_prompt *p);
bool	ensure_capacity(void **buffer, size_t *capacity,
			size_t needed, size_t elem_size);

#endif
