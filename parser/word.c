/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:30:57 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/28 11:41:16 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode *parse_word_node(t_token *token_list);
t_treenode *parse_word1(t_token *token_list);

//PARSE_WORD
t_treenode *parse_word_node(t_token *token_list)
{
	t_treenode *node;

	if (node = parse_word1(token_list))
		return (node);
	return (NULL)
}
t_treenode *parse_word1(t_token *token_list)
{
	t_treenode *node;

	if (token_list == NULL)
		return (NULL);
	if (token_list->type != WORD)
		return (NULL);
	node->left = NULL;
	node->right = NULL;
}
//PARSE_WORD END
