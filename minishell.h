/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:56:16 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/05 16:38:28 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include "libft/libft.h"

enum e_TOKEN_TYPE
{
	WORD,
	OPERATOR,
	PIPE, //|
	LOGICAL_OR, //||
	LOGICAL_AND, //&&
	SEMICOLON, //;
	INPUT_REDIRECTION, //<
	HERE_DOCUMENT, //>
	OUTPUT_REDIRECTION, //>>
	APPEND_OUTPUT_REDIRECTION, //<<
	SIMPLE_QUOTE, //'
	DOUBLE_QUOTE, //"
	BRACKETS_R, //(
	BRACKETS_L, //)
};

typedef struct s_token
{
	int				type;
	char			*str;
	struct s_token	*next;
}			t_token;

// Fonctions tokenisations
t_token	*create_token(int type, char *str);
void	add_token_end(t_token **token, t_token *new_token);
void	print_token_list(t_token *token_list);
void	free_token(t_token *token_list);
int		is_operator_logical(char c);
int		ft_istokenword(int c);

#endif
