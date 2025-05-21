/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:45:33 by npederen          #+#    #+#             */
/*   Updated: 2025/05/21 15:06:13 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"


// INIT NODE - ADD NODE - FREE NODE 
t_treenode	*create_treenode(int type, char *str)
{
	t_treenode	*new_node;

	new_node = ft_calloc(1, sizeof(t_treenode));
	if (new_node == NULL)
		return (NULL);
	new_node->type = type;
	new_node->str = str;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

void	add_node(t_treenode *parent_node, t_treenode *new_child, int dir)
{
	if (parent_node == NULL)
		parent_node = new_child;
	else
	{
		if (dir == 0)
			parent_node->left = new_child;
		else if (dir == 1)
			parent_node->right = new_child;
	}
}

void	free_treenode(t_treenode *treenode)
{
	if (!treenode)
	{
		if (treenode->str)
			free(treenode->str);
		free_treenode(treenode->left);
		free_treenode(treenode->right);
		free(treenode);
	}
}
t_treenode	*create_tree(t_token *token_list)
{
	t_treenode	*ast = NULL;
	t_treenode	*tmp = NULL;
	t_treenode	*tmp2 = NULL;
	
	while (token_list && token_list->type == WORD)
	{
		tmp2 = create_treenode(token_list->type, token_list->str);
		if (!ast)
		{
			ast = tmp2;
			tmp = ast;
		}
		else
		{
			add_node(tmp, tmp2, LEFT);
			tmp = tmp2;
		}
		token_list = token_list->next;
	}
	if (token_list && token_list->type != WORD)
	{
		tmp2 = create_treenode(token_list->type, token_list->str);
		add_node(tmp2, ast, LEFT);
		ast = tmp2;
		token_list = token_list->next;
	}
	tmp = ast;
	while (token_list && token_list->type == WORD)
	{
		tmp2 = create_treenode(token_list->type, token_list->str);
		add_node(tmp, tmp2, RIGHT);
		tmp = tmp2;
		token_list = token_list->next;
	}
	tmp = ast;
	while (tmp)
	{
		printf("%i", tmp->type);
		printf("[%s]", tmp->str);
		tmp = tmp->left;
	}
	while (ast->right)
	{
		ast = ast->right;
		printf("%i", ast->type);
		printf("[%s]", ast->str);
	}
	printf("\n");
	return (NULL);
}


