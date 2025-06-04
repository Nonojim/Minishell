/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:28:49 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/04 22:11:26 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_redirection_node(t_token **token_list);
t_treenode	*parse_redirection1(t_token **token_list);

t_treenode	*parse_redirection_node(t_token **token_list)
{
	t_treenode	*node;
	t_token		*tmp;

	node = NULL;
	tmp = *token_list;
	node = parse_redirection1(token_list);
	if (node != NULL)
		return (node);
	*token_list = tmp;
//	free_treenode(node);
	return (NULL);
}

t_treenode	*parse_redirection1(t_token **token_list)
{
	t_treenode	*node;
	t_treenode	*right;
	t_token		*create_node;

	node = NULL;
	right = NULL;
	if (*token_list == NULL)
		return (NULL);
	if ((*token_list)->type != INPUT_REDIRECTION
		&& (*token_list)->type != OUTPUT_REDIRECTION
		&& (*token_list)->type != HERE_DOCUMENT
		&& (*token_list)->type != APPEND_OUTPUT_REDIRECTION)
		return (NULL);
	create_node = *token_list;
	*token_list = (*token_list)->next;
	if (*token_list == NULL)
		return (NULL);
	right = parse_word_node(token_list);
	if (right == NULL)
		return (NULL);
	node = create_treenode(create_node->type, create_node->str);
	node->left = NULL;
	node->right = right;
	return (node);
}
