/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:28:49 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/28 12:24:32 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_redirection_node(t_token *token_list);
t_treenode	*parse_redirection1(t_token *token_list);
//t_treenode	*parse_redirection2(t_token *token_list);

t_treenode	*parse_redirection_node(t_token *token_list)
{
	t_treenode	*node;

	if ((node = parse_redirection1(token_list)))
		return (node);
	//if ((node = parse_redirection2(token_list)))
		//return (node);
	return (NULL);
}
t_treenode	*parse_redirection1(t_token *token_list)
{
	t_treenode	*node;
	t_treenode	*right;
//	t_treenode	*left;

	if (token_list->type != INPUT_REDIRECTION &&
		token_list->type != OUTPUT_REDIRECTION &&
		token_list->type != HERE_DOCUMENT &&
		token_list->type != APPEND_OUTPUT_REDIRECTION)
		return (NULL);
	if ((right = parse_word_node(token_list)) != NULL)
		return (NULL);
	
	node = create_treenode(token_list->type, token_list->str);
//	node->left = NULL;
	node->right = right;
	return (node);
}
