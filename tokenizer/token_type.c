/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:58:48 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/27 14:15:25 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

/*
* Determine the token type
 */
int	type_token_double_operator(char *str)
{
	if (str[0] == '|' && str[1] == '|' )
		return (LOGICAL_OR);
	else if (str[0] == '>' && str[1] == '>')
		return (APPEND_OUTPUT_REDIRECTION);
	else if (str[0] == '<' && str[1] == '<')
		return (HERE_DOCUMENT);
	else if (str[0] == '&' && str[1] == '&')
		return (LOGICAL_AND);
	return (0);
}

/*
* Determine the token type
 */
int	type_token(char *str)
{
	int	double_operator;

	double_operator = type_token_double_operator(str);
	if (double_operator)
		return (double_operator);
	else if (str[0] == '|')
		return (PIPE);
	else if (str[0] == ';')
		return (SEMICOLON);
	else if (str[0] == '<')
		return (INPUT_REDIRECTION);
	else if (str[0] == '>')
		return (OUTPUT_REDIRECTION);
	else if (str[0] == '(')
		return (BRACKETS_L);
	else if (str[0] == ')')
		return (BRACKETS_R);
	else
		return (WORD);
}


