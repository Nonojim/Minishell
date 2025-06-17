/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:29:26 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/17 14:21:26 by lduflot          ###   ########.fr       */
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

	simple_cmd_node = NULL;
	tmp = *tokens;
	if (parse_error(-1) == 1)
		return (NULL);
	simple_cmd_node = parse_simple_command1(tokens);
	if (simple_cmd_node != NULL && parse_error(-1) == 0)
		return (simple_cmd_node);
	*tokens = tmp;
	simple_cmd_node = parse_simple_command2(tokens);
	if (simple_cmd_node != NULL && parse_error(-1) == 0)
		return (simple_cmd_node);
	*tokens = tmp;
	simple_cmd_node = parse_simple_command3(tokens);
	if (simple_cmd_node != NULL && parse_error(-1) == 0)
		return (simple_cmd_node);
	*tokens = tmp;
	return (NULL);
}

//word _ redirection _ word
t_treenode	*parse_simple_command1(t_token **tokens)
{
	t_treenode	*word_node;
	t_treenode	*redir_node;
	t_treenode	*left;

	word_node = NULL;
	redir_node = NULL;
	left = parse_word_node(tokens);
	if (left == NULL)
		return (NULL);
	redir_node = parse_redirection_node(tokens);
	while (redir_node != NULL)
	{
		redir_node->left = left;
		word_node = redir_node;
		left = word_node;
		redir_node = parse_redirection_node(tokens);
	}
	if (word_node == NULL)
		return (free_then_return_null(left));
	return (word_node);
}

//redirection _ word
t_treenode	*parse_simple_command2(t_token **tokens)
{
	t_treenode	*word_node;
	t_treenode	*redir_node;
	t_treenode	*left;
	t_token		*tmp;

	word_node = NULL;
	redir_node = NULL;
	left = parse_word_node(tokens);
	if (left != NULL)
		return (free_then_return_null(left));
	tmp = *tokens;
	redir_node = parse_redirection_node(tokens);
	while (redir_node != NULL)
	{
		redir_node->left = word_node;
		word_node = redir_node;
		redir_node = parse_redirection_node(tokens);
	}
	if (word_node == NULL)
		return (free_settoken_thenreturn(left, tokens, tmp));
	return (word_node);
}

//word
t_treenode	*parse_simple_command3(t_token **tokens)
{
	t_treenode	*word_node;

	word_node = NULL;
	word_node = parse_word_node(tokens);
	return (word_node);
}
