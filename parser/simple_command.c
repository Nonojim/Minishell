/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:29:26 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/16 20:05:51 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_simple_command_node(t_token **tokens);
t_treenode	*parse_simple_command1(t_token **tokens);
t_treenode	*parse_simple_command2(t_token **tokens);
t_treenode	*parse_simple_command3(t_token **tokens);

/*
 <simple_command>      ::= <word> ( <word> | <redirection> )*
												|	<word> <redirection> word
												|	<word>
*/
t_treenode	*parse_simple_command_node(t_token **tokens)
{
	t_treenode	*simple_cmd_node;
	t_token		*tmp;

	tmp = *tokens;
	if (parse_error(-1) == 1)
		return (NULL);
	if ((simple_cmd_node = parse_simple_command1(tokens)))
	{
		if (parse_error(-1) == 1)
			return (NULL);
		return (simple_cmd_node);
	}
	*tokens = tmp;
	if ((simple_cmd_node = parse_simple_command2(tokens)))
	{
		if (parse_error(-1) == 1)
			return (NULL);
		return (simple_cmd_node);
	}
	*tokens = tmp;
	if ((simple_cmd_node = parse_simple_command3(tokens)))
	{
		if (parse_error(-1) == 1)
			return (NULL);
		return (simple_cmd_node);
	}
	*tokens = tmp;
	return (NULL);
}

//word _ redirection _ word
t_treenode	*parse_simple_command1(t_token **tokens)
{
	t_treenode	*word_node;
	t_treenode	*redir_node;
	t_treenode	*left;

	if ((left = parse_word_node(tokens)) == NULL)
		return (NULL);
	while ((redir_node = parse_redirection_node(tokens)) != NULL)
	{
		redir_node->left = left;
		word_node = redir_node;
		left = word_node;
	}
	if (word_node == NULL)
		return (free_then_return_null(left));
	return (word_node);
}

//redirection _ word
t_treenode	*parse_simple_command2(t_token **tokens)
{
	t_treenode	*word_node = NULL;
	t_treenode	*redir_node = NULL;
	t_treenode	*left = NULL;

	if ((left = parse_word_node(tokens)) != NULL)
		return (free_then_return_null(left));
	t_token *tmp = *tokens;
	while((redir_node = parse_redirection_node(tokens)) != NULL)
	{
		redir_node->left = NULL;
		word_node = redir_node;
	}
	if (word_node == NULL)
		return (free_settoken_thenreturn(left, tokens, tmp));
	return (word_node);
}

//word
t_treenode	*parse_simple_command3(t_token **tokens)
{
	t_treenode	*word_node = NULL;

	word_node = parse_word_node(tokens);
	return (word_node);
}
