/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:28:49 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/11 18:38:45 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_redirection_node(t_token **token_list);
t_treenode	*parse_redirection1(t_token **token_list);

/*
<redirection>				::= ( "<" | "<<" | ">" | ">>" ) <word>
*/
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
	if (!is_redirection((*token_list)->type))
		return (NULL);
	create_node = *token_list;
	*token_list = (*token_list)->next;
	if (*token_list == NULL || !is_word_type((*token_list)->type))
	{
		*token_list = create_node;
			return (NULL);
	}
	//printf("%p\n", (*token_list)->str);
	right = parse_word_node(token_list);
	if (right == NULL)
	{
		*token_list = create_node;
		return (NULL);
	}
	node = create_treenode(create_node->type, create_node->str);
	create_node = *token_list;
	if (node == NULL)
	{
		free_treenode(right);
		return (NULL);
	}
	node->right = right;
	return (node);
}
