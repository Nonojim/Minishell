/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:56:16 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/26 08:04:01 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_token t_token;
typedef struct s_treenode t_treenode;
typedef struct s_env t_env;

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

#endif
