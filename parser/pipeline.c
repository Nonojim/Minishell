/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:28:31 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/04 23:07:30 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_pipeline_node(t_token **token_list);
t_treenode	*parse_pipeline1(t_token **token_list);
t_treenode	*parse_pipeline2(t_token **token_list);

t_treenode	*parse_pipeline_node(t_token **token_list)
{
	t_token		*tmp;
	t_treenode	*node;

	tmp = *token_list;
	node = NULL;
	node = parse_pipeline1(token_list);
	if (node != NULL)
		return (node);
	*token_list = tmp;
	//free_treenode(node);
	node = parse_pipeline2(token_list);
	if (node != NULL)
		return (node);
	*token_list = tmp;
	//free_treenode(node);
	return (NULL);
}

t_treenode	*parse_pipeline1(t_token **token_list)
{
t_treenode	*left;
	t_treenode	*right;
	t_treenode	*node;
	t_token		*create_node;

	left = parse_command_node(token_list);
	if (left == NULL)
		return (NULL);

	while (*token_list != NULL && (*token_list)->type == PIPE)
	{
		create_node = *token_list;
		*token_list = (*token_list)->next;

		right = parse_command_node(token_list);
		if (right == NULL)
			return (NULL); // erreur de syntaxe

		node = create_treenode(create_node->type, create_node->str);
		node->left = left;
		node->right = right;

		left = node; // nouvelle racine = pipe
	}
	return (left);
}

t_treenode	*parse_pipeline2(t_token **token_list)
{
	t_treenode	*node;

	node = NULL;
	return (node = parse_command_node(token_list));
}
