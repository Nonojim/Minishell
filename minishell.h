/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:56:16 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/28 10:02:20 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "typedef.h"

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
# include "tokenizer/tokenizer.h"
# include "parser/ast.h"
# include "expansion/expansion.h"
# include "signal/signal.h"
# include "execution/builtins/builtins.h"
# include "execution/execution.h"

//main.c
void	token_not_empty(t_token **token, t_treenode **ast, t_token *tmp);
int		signal_interrupt(char *line, t_ctx *ctx);
void	main_loop(t_ctx *ctx);
void	resolve_ast(t_treenode *ast, char *line, t_ctx *ctx);
void	token_not_empty(t_token **token, t_treenode **ast, t_token *tmp);
//mains_utils
t_ctx	init_ctx(void);
void	start_message(void);
void	free_prompt(t_treenode *ast, char *line);
#endif
