/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ezprompt.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgingast <mgingast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:23:08 by mgingast          #+#    #+#             */
/*   Updated: 2025/09/19 17:09:15 by mgingast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EZPROMPT_H
# define EZPROMPT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <termios.h>

typedef struct s_prompt
{
	/* Prompt & input */
	char	*prompt;
	char	*input;
	int		input_size;
	int		input_capacity;

	/* History */
	char	**history;
	int		history_size;
	int		max_history;
	int		history_index;

	/* Global states */
	int		exit_flag;
}			t_prompt;

typedef enum e_arrow
{
	ARROW_NONE,
	ARROW_UP,
	ARROW_DOWN,
	ARROW_LEFT,
	ARROW_RIGHT
}		t_arrow;

/* Core */
bool	next_read(t_prompt *p);

/* History and arrow */
void	set_history_up(t_prompt *p);
void	set_history_down(t_prompt *p);
t_arrow	get_arrow(void);
bool	play_arrow(t_prompt *p);

/* Utils */
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(const char *str);
char	*ft_strdup(const char *str);
char	*resize(char *old, int n, bool free_old);

/* Skipable */
bool	is_l(char c, t_prompt *p);
bool	is_d(char c, t_prompt *p);
bool	is_backspace(char c, t_prompt *p);
bool	is_empty(char *str);
bool	is_skipable(char c, t_prompt *p);

/* Free */
void	free_tab(char **tab);
void	free_prompt(t_prompt *p);

/* Init */
bool	init_prompt(t_prompt *p, char *prompt);
bool	clear_input(t_prompt *p);

/* memory */
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

#endif
