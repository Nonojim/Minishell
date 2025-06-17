/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:28:31 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/17 13:08:06 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_pipeline_node(t_token **tokens);
t_treenode	*parse_pipeline1(t_token **tokens);
t_treenode	*parse_pipeline2(t_token **tokens);

t_treenode	*parse_pipeline_node(t_token **tokens)
{
	t_token		*tmp;
	t_treenode	*pipe_node;

	tmp = *tokens;
	pipe_node = NULL;
	if (parse_error(-1) == 1)
		return (NULL);
	pipe_node = parse_pipeline1(tokens);
	if (parse_error(-1) == 1)
		return (NULL);
	if (pipe_node != NULL)
		return (pipe_node);
	*tokens = tmp;
	pipe_node = parse_pipeline2(tokens);
	if (parse_error(-1) == 1)
		return (NULL);
	if (pipe_node != NULL)
		return (pipe_node);
	*tokens = tmp;
	return (NULL);
}

//<command> "|" <command>
//Conservation du noeuf left (word) même si pas de pipeline,
//evite de reparser.
t_treenode	*parse_pipeline1(t_token **tokens)
{
	t_treenode	*left;
	t_treenode	*right;
	t_treenode	*pipe_node;
	t_token		*pipe_token;

	pipe_node = NULL;
	if (*tokens == NULL || (!is_redirection((*tokens)->type)
			&& (*tokens)->type != BRACKETS_L && !is_word_type((*tokens)->type)))
		return (printerror_then_return_null(tokens));
	left = parse_command_node(tokens);
	if (left == NULL)
		return (NULL);
	if (*tokens == NULL || (*tokens)->type != PIPE)
		return (left);
	pipe_token = *tokens;
	*tokens = (*tokens)->next;
	if (*tokens == NULL || (*tokens != NULL && !is_word_type((*tokens)->type)))
		return (printerror_free_return_null(tokens, left));
	right = parse_pipeline1(tokens);
	if (right == NULL)
		return (free_then_return_null(left));
	pipe_node = create_treenode(pipe_token->type, pipe_token->str);
	pipe_node->left = left;
	pipe_node->right = right;
	return (pipe_node);
}

//<command>
t_treenode	*parse_pipeline2(t_token **tokens)
{
	t_treenode	*command_node;

	command_node = NULL;
	return (command_node = parse_command_node(tokens));
}
