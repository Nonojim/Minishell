/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:21:27 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/27 16:03:34 by lduflot          ###   ########.fr       */
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
	SIMPLE_QUOTE, //' 9 ASCII = 39
	DOUBLE_QUOTE, //" 10 ASCII = 34
	BRACKETS_R, //( 11 ASCII = 40
	BRACKETS_L, //) 12 ASCII = 41
//	EXPANSION, //$ 13 ASCII = 36
};

typedef struct s_token
{
	int				type;
	char			*str;
	struct s_token	*next;
}			t_token;

// Fonctions tokenisations
//tokenize the input
t_token	*tokenize(t_token *token, char **line);
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
char	*token_logical_incomplete(int *i, int start, char *line, t_token **token);
int		only_spaces_after_operator_logical(char *line, int i);
char	*token_bracket_incomplete(char *line);
char	*token_bracket(int *i, int start, char *line, t_token **token);
//Token_quote
char	*read_until_quote_closed(char *line, char quote);
char	*token_quote(int *i, int start, char *line, t_token **token);

#endif
