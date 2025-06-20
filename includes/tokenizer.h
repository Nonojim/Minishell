/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:21:27 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/20 01:36:40 by lduflot          ###   ########.fr       */
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
	HERE_DOC_DELETE_TAB, //<<-
	START_DELIMITATEUR,
	END_DELIMITATEUR,
	INSIDE_HERE_DOC,
	//SIMPLE_QUOTE, //' 9 ASCII = 39
	//DOUBLE_QUOTE, //" 10 ASCII = 34
	BRACKETS_L, //( 11 ASCII = 40
	BRACKETS_R, //) 12 ASCII = 41
	EXPANSION, //$ 13 ASCII = 36
};

typedef struct s_token
{
	int				type;
	char			*str;
	struct s_token	*next;
	struct s_token	*here_doc_tokens;
}			t_token;

// Fonctions tokenisations
//tokenize the input
t_token	*tokenize(t_token *token, char **line);
char	*tokenize2(int	*i, int start, char *line, t_token **token);
//Create_free_print Token
t_token	*create_token(int type, char *str);
void	add_token_end(t_token **token, t_token *new_token);
void	print_token_list(t_token *token_list);
void	free_token(t_token *token_list);
//Type Token
int		type_token(char *str);
int		type_token_double_operator(char *str);
//Token_word
int		is_word(int c);
void	token_word(int *i, int start, char *line, t_token **token);
//Token_operator
int		is_operator_logical(char c);
int		is_ok_double(char c);
void	token_logical_operator(int *i, int start, char *line, t_token **token);
int		is_orlogical_andlogical(char c);
char	*token_pipe_unclose(int *i, int start, char *line, t_token **token);
char	*token_logical_unclose(int *i, int start, char *line, t_token **token);
int		only_spaces_after_operator_logical(char *line, int i);
char	*token_bracket_unclose(char *line);
void	bracket_unclosed(char **line, char **history_line, char*next_line);
char	*token_bracket(int *i, int start, char *line, t_token **token);
int		count_matching_bracket(char *str);
void	token_expansion(int *i, int start, char *line, t_token **token);
//Token_quote
char	*read_until_quote_closed(char *line, char quote);
char	*token_quote(int *i, int start, char *line, t_token **token);
//Token_HereDoc
char	*open_heredoc(int *i, int start, char *line, t_token **token);

#endif
