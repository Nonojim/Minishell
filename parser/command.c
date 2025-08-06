/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:29:59 by lduflot           #+#    #+#             */
/*   Updated: 2025/08/06 17:47:09 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_command_node(t_token **tokens)
{
	t_token		*tmp;
	t_treenode	*node;

	tmp = *tokens;
	node = NULL;
	if (parse_error(-1) == 1)
		return (NULL);
	node = parse_command_node1(tokens);
	if (parse_error(-1))
		return (NULL);
	if (node)
		return (node);
	*tokens = tmp;
	node = parse_command_node2(tokens);
	if (parse_error(-1) == 1)
		return (NULL);
	if (node)
		return (node);
	*tokens = tmp;
	return (NULL);
}

t_treenode	*parse_command_node1(t_token **tokens)
{
	t_token		*tmp;
	t_treenode	*line_node;
	t_treenode	*subshell_node;

	tmp = *tokens;
	if (*tokens == NULL || (*tokens)->type != BRACKETS_L)
		return (NULL);
	*tokens = (*tokens)->next;
	line_node = parse_line_node(tokens);
	if (line_node == NULL || *tokens == NULL || (*tokens)->type != BRACKETS_R)
		return (free_settoken_thenreturn(line_node, tokens, tmp));
	*tokens = (*tokens)->next;
	subshell_node = create_treenode(SUBSHELL, "()");
	subshell_node->left = line_node;
	if (line_node && line_node->type == SUBSHELL && line_node->left
		&& line_node->left->argv && line_node->left->argv[1] == NULL)
		return (free_settoken_thenreturn(subshell_node, tokens, NULL));
	line_node = parse_redirection_node(tokens);
	while (line_node != NULL)
	{
		line_node->left = subshell_node;
		subshell_node = line_node;
		line_node = parse_redirection_node(tokens);
	}
	return (subshell_node);
}

t_treenode	*free_settoken_thenreturn(t_treenode *nodetofree,
	t_token **tokenstoset, t_token *setting)
{
	free_treenode(nodetofree);
	*tokenstoset = setting;
	return (NULL);
}

// simple_command
t_treenode	*parse_command_node2(t_token **tokens)
{
	t_treenode	*simple_cmd_node;

	simple_cmd_node = parse_simple_command_node(tokens);
	return (simple_cmd_node);
}
