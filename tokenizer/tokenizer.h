/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:21:27 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/28 18:54:57 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../minishell.h"

enum e_TOKEN_TYPE
{
	WORD, //0
	PIPE, //| 1 ASCII = 124
	LOGICAL_OR, //|| 2 ASCII = 124,124
	LOGICAL_AND, //&& 3 ASCII = 38,38
	SEMICOLON, //; 4 ASCII = 59
	INPUT_REDIRECTION, //< 5 ASCII = 60
	HERE_DOCUMENT, //> 6 ASCII = 60,60
	OUTPUT_REDIRECTION, //>> 7 ASCII = 62
	APPEND_OUTPUT_REDIRECTION, //<< 8 ASCII = 62,62
	INSIDE_HERE_DOC,
	BRACKETS_L, //( 11 ASCII = 40
	BRACKETS_R, //) 12 ASCII = 41
	EXPANSION, //$ 13 ASCII = 36
	SUBSHELL, //() 14
};

typedef struct s_token
{
	int				type;
	char			*str;
	struct s_token	*next;
	struct s_token	*here_doc_tokens;
}			t_token;

typedef struct s_token_info
{
	int			*i;
	int			start;
	char		*line;
	t_token		**token;
	t_ctx		*env;
}	t_token_info;

typedef struct s_heredoc_info
{
	char	*line;
	char	*next_line;
	char	*heredoc_line;
	char	*buffer;
	char	tmp[1024];
	pid_t	pid;
	int		fd[2];
	int		status;
	ssize_t	bytes;
	int		line_error;
}	t_heredoc_info;

// Fonctions tokenisations
t_token	*tokenize(t_token *token, char **line, t_ctx *ctx);
char	*tokenize2(t_token_info *info);

// Create_free_print Token
t_token	*create_token(int type, char *str);
void	add_token_end(t_token **token, t_token *new_token);
void	print_token_list(t_token *token_list);
void	free_token(t_token *token_list);

// Type Token
int		type_token(char *str);
int		type_token_double_operator(char *str);

// Token_word
int		is_word(int c);
char	*token_word(t_token_info *info);
char	*add_token_word(int *i, int start, char *line, t_token **token);

// Token_operator
int		is_operator_logical(char c);
int		is_ok_double(char c);
void	token_logical_operator(t_token_info *info);
int		is_orlogical_andlogical(char c);
char	*token_pipe_unclose(t_token_info *info);
char	*token_logical_unclose(t_token_info *info);
int		only_spaces_after_operator_logical(char *line, int i);

// Token_bracket
char	*token_bracket_unclose(char *line);
void	bracket_unclosed(char **line, char **history_line, char *next_line);
char	*token_bracket(t_token_info *info);
int		count_matching_bracket(char *str);

// Token_expansion
void	token_expansion(int *i, int start, char *line, t_token **token);

// Erreurs et vérifs opérateurs
void	free_unclose_logical(char *tmp, char *next_line, char *line);
int		print_error_logical(char *line, int *j, t_ctx *ctx, int error);
int		type_token_operator(char *str);
int		type_token_redir(char *str);
int		only_space_after_op(char *line, int i);
int		only_space_before(char *line, int i);
int		only_spaces_after_pipe(char *line, int i);
int		check_error_after_logical(char *line, int *i, t_ctx *ctx);
int		check_redir_before_logical(char *line, int *i, t_ctx *ctx);
int		check_error_after_pipe(char *line, int *i, t_ctx *ctx);

// Token_quote
char	*read_until_quote_closed(char *line, char quote);
char	*token_quote(t_token_info *info);
char	*quote_interrupt(char *next_line, int signum);
char	*read_quote_loop(char *line, char quote);
char	*create_new_line(char *line, char *next_line);

// Token_HereDoc
char	*open_heredoc(t_token_info *info);
char	*newline_heredoc(char *token_doc, int j, t_token **token, t_ctx *ctx);
int		create_token_op_heredoc(char *line, int *i, t_token **token);
char	*delete_tab_or_ad_return_line(char *next_line, int j);
void	add_heredoc_token(t_token **token, char *token_doc, char *heredoc_line);
char	*delete_quote(char *str, t_token **token);
void	free_heredoc(char *line, char *token_doc, t_token **token, t_ctx *ctx);

#endif
