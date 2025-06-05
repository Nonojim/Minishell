/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:30:57 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/05 12:46:25 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_word_node(t_token **token_list);
t_treenode	*parse_word1(t_token **token_list);

t_treenode	*parse_word_node(t_token **token_list)
{
	t_treenode	*node;
	t_token		*tmp;

	node = NULL;
	tmp = *token_list;
	node = parse_word1(token_list);
	if (node)
		return (node);
	*token_list = tmp;
	free_treenode(node);
	return (NULL);
}

//[WORD token]
t_treenode	*parse_word1(t_token **token_list)
{
	t_treenode	*node;

	node = NULL;
	return (node = create_branch_words(token_list));
}
