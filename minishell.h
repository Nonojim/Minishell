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

//debute automatiquement l enum a 0;
enum TOKEN_TYPE
{
WORD,
PIPE,
LOGICAL_OR,
LOGICAL_AND,
SEMICOLON,
INPUT_REDIRECTION,
HERE_DOCUMENT,
OUTPUT_REDIRECTION,
APPEND_OUTPUT_REDIRECTION,
SIMPLE_QUOTE,
DOUBLE_QUOTE,
BRACKETS_R,
BRACKETS_L,
};

typedef struct s_token
{
	int	type;
	char	*str;
 	struct s_token *next;
}			t_token;

#endif
