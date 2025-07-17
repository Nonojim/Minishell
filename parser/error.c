/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:36:05 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/15 10:50:37 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/*
	* State :
* -1 = lecture dans les bloc parsing pour vérifier l'état de l'erreur
*  0 = on remet à zéro la static (nouveau prompt)
*  1 = erreur détecté 
	*/
int	parse_error(int state)
{
	static int	error = 0;

	if (state == -1)
		return (error);
	if (state == 0)
		error = 0;
	else if (state == 1)
		error = 1;
	return (error);
}

void	print_error(t_token *tokens)
{
	if (parse_error(-1))
		return ;
	if (tokens == NULL)
	{
		parse_error(1);
		fprintf(stderr, "minishell: syntax error near unexpected token `newline'\n");
		return ;
	}
	parse_error(1);
	if (is_op_logique(tokens->type) || is_word_type(tokens->type))
		fprintf(stderr, "minishell: syntax error near unexpected token '%s'\n",
			tokens->str);
	if (is_redirection(tokens->type) && tokens->next != NULL
		&& is_redirection(tokens->next->type))
	{
		fprintf(stderr, "minishell: syntax error near unexpected token '%s'\n",
			tokens->next->str);
		return ;
	}
	if (is_redirection(tokens->type))
		fprintf(stderr, "minishell: syntax error near unexpected token `newline'\n");
	if (is_bracket(tokens->type))
		fprintf(stderr, "minishell: syntax error near unexpected token '%s'\n",
			tokens->str);
}

t_treenode	*printerror_then_return_null(t_token **tokens)
{
	print_error(*tokens);
	return (NULL);
}

t_treenode	*printerror_free_return_null(t_token **tokens, t_treenode *node)
{
	print_error(*tokens);
	return (free_then_return_null(node));
}
