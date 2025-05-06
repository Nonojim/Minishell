/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:56:16 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/06 02:54:35 by lduflot          ###   ########.fr       */
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
	WORD, //0
	PIPE, //| 1
	LOGICAL_OR, //|| 2
	LOGICAL_AND, //&& 3
	SEMICOLON, //; 4
	INPUT_REDIRECTION, //< 5
	HERE_DOCUMENT, //> 6
	OUTPUT_REDIRECTION, //>> 7
	APPEND_OUTPUT_REDIRECTION, //<< 8
	SIMPLE_QUOTE, //' 9
	DOUBLE_QUOTE, //" 10
	BRACKETS_R, //( 11
	BRACKETS_L, //) 12
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
