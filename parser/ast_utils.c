/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:45:33 by npederen          #+#    #+#             */
/*   Updated: 2025/06/11 10:17:10 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	print_indent(int depth)
{
	while (depth-- > 0)
		printf("  ");
}

int	is_word_type(int type)
{
    return (type == WORD
            || type == SIMPLE_QUOTE
            || type == DOUBLE_QUOTE
            || type == EXPANSION);
}

void	astreeprint(t_treenode *node, int depth)
{
	int i = 0;
	if (!node)
		return ;
	print_indent(depth);
	printf("[Type: %i", node->type);
	if (node->str)
		printf(", data: \"%s\"]", node->str);
	if (node->argv)
	{
		printf(", argv: [");
		i = 0;
		while (node->argv[i])
		{
			printf("\"%s\"", node->argv[i]);
			if (node->argv[i + 1])
				printf(", ");
			i++;
		}
		printf("]");
	}
	printf("\n");
	if (node->left)
	{
		print_indent(depth);
		printf("Left:\n");
		astreeprint(node->left, depth + 1);
	}
	if (node->right)
	{
		print_indent(depth);
		printf("Right:\n");
		astreeprint(node->right, depth + 1);
	}
}

extern int g_node_count;
// INIT NODE - ADD NODE - FREE NODE 
t_treenode	*create_treenode(int type, char *str)
{
	t_treenode	*new_node;

	new_node = ft_calloc(1, sizeof(t_treenode));
	if (new_node == NULL)
		return (NULL);
	g_node_count++;
	//printf("CREATE NODE: %d (%s)\n", g_node_count, str ? str : "NULL");
	new_node->type = type;
	if (str)
		new_node->str = ft_strdup(str); //evite le partage de memoire; les doubles free etc
	new_node->argv = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

void	free_treenode(t_treenode *node)
{
	int i = 0;
	if (node == NULL)
		return ;
	free_treenode(node->left);
	node->left = NULL;
	free_treenode(node->right);
	node->right = NULL;
	if (node->str != NULL)
	{
		//printf("free str: %s\n", node->str);
		free(node->str);
		node->str = NULL;
	}
	if (node->argv != NULL)
	{
		while (node->argv[i] != NULL)
		{
			free(node->argv[i]);
			i++;
		}
		free(node->argv);
		node->argv = NULL;
	}
	//printf("FREE NODE: %d\n", g_node_count);
		g_node_count--;
	free(node);
	node = NULL;
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

t_treenode	*create_branch_words(t_token **token_list)
{
	t_treenode	*root = NULL;
	t_treenode	*current = NULL;
	t_treenode	*new_node = NULL;

	while (*token_list != NULL
		&& ((*token_list)->type == WORD
	|| (*token_list)->type == EXPANSION
	|| (*token_list)->type == SIMPLE_QUOTE
	|| (*token_list)->type == DOUBLE_QUOTE ))
	{
		new_node = create_treenode((*token_list)->type, (*token_list)->str);
		if (!new_node || !new_node->str)
		{
			free_treenode(root);
			return (NULL);
		}
		if (!root)
		{
			root = new_node;
			current = root;
		}
		else
		{
			add_node(current, new_node, LEFT);
			current = new_node;
		}
		*token_list = (*token_list)->next;
	}
	return (root);
}
