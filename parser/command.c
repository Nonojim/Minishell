/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:29:59 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/05 11:49:19 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_command_node(t_token **token_list);
t_treenode	*parse_command_node1(t_token **token_list);
t_treenode	*parse_command_node2(t_token **token_list);
t_treenode	*parse_command_node3(t_token **token_list);
t_treenode	*parse_command_node4(t_token **token_list);
t_treenode	*parse_command_node5(t_token **token_list);

t_treenode	*parse_command_node(t_token **token_list)
{
	t_token		*tmp;
	t_treenode	*node;

	tmp = *token_list;
	node = NULL;
	node = parse_command_node1(token_list);
	if (node)
		return (node);
	*token_list = tmp;
	free_treenode(node);
	node = parse_command_node2(token_list);
	if (node)
		return (node);
	*token_list = tmp;
	free_treenode(node);
	node = parse_command_node3(token_list);
	if (node)
		return (node);
	*token_list = tmp;
	free_treenode(node);
	node = parse_command_node4(token_list);
	if (node)
		return (node);
	*token_list = tmp;
	free_treenode(node);
	node = parse_command_node5(token_list);
	if (node)
		return (node);
	*token_list = tmp;
	free_treenode(node);
	return (NULL);
}

// 	"(" <line> ")"
t_treenode	*parse_command_node1(t_token **token_list)
{
	t_treenode	*node;
	t_token		*tmp;
	t_treenode	*right;
	t_treenode	*left;

	node = NULL;
	right = NULL;
	left = NULL;
	left = parse_simple_command_node(token_list);
	if (left != NULL)
		return (NULL);
	if (*token_list == NULL || (*token_list)->type != BRACKETS_R)
	{
		free_treenode(left);
		return (NULL);
	}
	tmp = *token_list;
	*token_list = (*token_list)->next;
	while ((*token_list)->type != BRACKETS_L && *token_list != NULL)
	{
		*token_list = (*token_list)->next;
	}
	if ((*token_list)->type == BRACKETS_L && *token_list != NULL)
	{
		*token_list = tmp;
		node = create_treenode(SUBSHELL, "()");
		*token_list = (*token_list)->next;
		node->left = parse_line_node(token_list);
		if (node->left == NULL)
		{
			free_treenode(node);
			return (NULL);
		}
		if (*token_list == NULL || (*token_list)->type != BRACKETS_L)
		{
			free_treenode(node);
			return (NULL);
		}
		*token_list = (*token_list)->next;
		right = parse_simple_command_node(token_list);
		if (right != NULL)
		{
			free_treenode(right);
			free_treenode(node);
			return (NULL);
		}
		return (node);
	}
	else
	{
		*token_list = tmp;
		*token_list = (*token_list)->next;
		return (NULL);
	}
}

//simple_command "(" <line> ")"
t_treenode	*parse_command_node2(t_token **token_list)
{
	t_treenode	*node;
	t_token		*tmp;
	t_treenode	*left;
	t_treenode	*right;

	node = NULL;
	left = NULL;
	right = NULL;
	left = parse_simple_command_node(token_list);
	if (left == NULL)
		return (NULL);
	if (*token_list == NULL || (*token_list)->type != BRACKETS_R)
	{
		free_treenode(left);
		return (NULL);
	}
	tmp = *token_list;
	*token_list = (*token_list)->next;
	while ((*token_list)->type != BRACKETS_L && *token_list != NULL)
		*token_list = (*token_list)->next;
	if ((*token_list)->type == BRACKETS_L && *token_list != NULL)
	{
		*token_list = tmp;
		node = create_treenode(SUBSHELL, "()");
		*token_list = (*token_list)->next;
		node->right = parse_line_node(token_list);
		if (node->right == NULL)
		{
			free_treenode(node);
			return (NULL);
		}
		if (*token_list == NULL || (*token_list)->type != BRACKETS_L)
		{
			free_treenode(node);
			return (NULL);
		}
		*token_list = (*token_list)->next;
		right = parse_simple_command_node(token_list);
		if (right != NULL)
		{
			free_treenode(right);
			free_treenode(node);
			return (NULL);
		}
		node->left = left;
		return (node);
	}
	else
	{
		*token_list = tmp;
		*token_list = (*token_list)->next;
		return (NULL);
	}
}

//"(" <line> ")" simple_command
t_treenode	*parse_command_node3(t_token **token_list)
{
	t_treenode	*node;
	t_token		*tmp;
	t_treenode	*right;

	node = NULL;
	right = NULL;
	if (*token_list == NULL || (*token_list)->type != BRACKETS_R)
		return (NULL);
	tmp = *token_list;
	*token_list = (*token_list)->next;
	while ((*token_list)->type != BRACKETS_L && *token_list != NULL)
		*token_list = (*token_list)->next;
	if ((*token_list)->type == BRACKETS_L && *token_list != NULL)
	{
		*token_list = tmp;
		node = create_treenode(SUBSHELL, "()");
		*token_list = (*token_list)->next;
		node->left = parse_line_node(token_list);
		if (node->left == NULL)
		{
			free_treenode(node);
			return (NULL);
		}
		if (*token_list == NULL || (*token_list)->type != BRACKETS_L)
		{
			free_treenode(node);
			return (NULL);
		}
		*token_list = (*token_list)->next;
		right = parse_simple_command_node(token_list);
		if (right == NULL)
		{
			free_treenode(right);
			free_treenode(node);
			return (NULL);
		}
		node->right = right;
		return (node);
	}
	else
	{
		*token_list = tmp;
		*token_list = (*token_list)->next;
		return (NULL);
	}
}

//simple_command "(" <line> ")" simple_command
t_treenode	*parse_command_node4(t_token **token_list)
{
	t_treenode	*node;
	t_token		*tmp;
	t_treenode	*left;
	t_treenode	*right;

	node = NULL;
	left = NULL;
	right = NULL;
	left = parse_simple_command_node(token_list);
	if (left == NULL)
		return (NULL);
	if (*token_list == NULL || (*token_list)->type != BRACKETS_R)
	{
		free_treenode(left);
		return (NULL);
	}
	tmp = *token_list;
	*token_list = (*token_list)->next;
	while ((*token_list)->type != BRACKETS_L && *token_list != NULL)
		*token_list = (*token_list)->next;
	if ((*token_list)->type == BRACKETS_L && *token_list != NULL)
	{
		*token_list = tmp;
		node = create_treenode(SUBSHELL, "()");
		*token_list = (*token_list)->next;
		node->right = parse_line_node(token_list);
		if (node->right == NULL)
		{
			free_treenode(node);
			return (NULL);
		}
		if (*token_list == NULL || (*token_list)->type != BRACKETS_L)
		{
			free_treenode(node);
			return (NULL);
		}
		*token_list = (*token_list)->next;
		right = parse_simple_command_node(token_list);
		if (right == NULL)
		{
			free_treenode(right);
			free_treenode(node);
			return (NULL);
		}
		node->left = left;
		node->right = right;
		return (node);
	}
	else
	{
		*token_list = tmp;
		*token_list = (*token_list)->next;
		return (NULL);
	}
}

//simple_command
t_treenode	*parse_command_node5(t_token **token_list)
{
	t_treenode	*node;

	node = NULL;
	return (node = parse_simple_command_node(token_list));
}
