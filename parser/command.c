/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:29:59 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/28 12:17:50 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_command_node(t_token *token_list);
t_treenode	*parse_command_node1(t_token *token_list);
t_treenode	*parse_command_node2(t_token *token_list);

t_treenode	*parse_command_node(t_token *token_list)
{
	t_treenode	*node;

	if ((node = parse_command_node1(token_list)))
		return (node);
	if ((node = parse_command_node2(token_list)))
		return (node);
	return (NULL);
}

t_treenode	*parse_command_node1(t_token *token_list)
{
	t_treenode	*node;
	//t_treenode	*left;
	t_treenode	*right;

	if (token_list->type != BRACKETS_L)
		return (NULL);
	if ((right = parse_line_node(token_list)) != NULL)
		return (NULL);
	if (token_list->type != BRACKETS_R)
		return (NULL);
	if ((right = parse_command_node1(token_list)) != NULL)
		return (NULL);
	node = create_treenode(token_list->type, token_list->str);
	//node->left = NULL;
	node->right = right;
	return (node);
}

t_treenode	*parse_command_node2(t_token *token_list)
{
	t_treenode	*node;

	return (node = parse_simple_command_node(token_list));
}
