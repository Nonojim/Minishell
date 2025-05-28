/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:29:26 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/28 12:20:42 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_simple_command_node(t_token *token_list);
t_treenode	*parse_simple_command1(t_token *token_list);
t_treenode	*parse_simple_command2(t_token *token_list);

t_treenode	*parse_simple_command_node(t_token *token_list)
{
	t_treenode	*node;

	if ((node = parse_simple_command1(token_list)))
		return (node);
	if ((node = parse_simple_command2(token_list)))
		return (node);
	return (NULL);
}

//no priorité ds les redirection, prio dans le sens de lecture (gauche à droite)
t_treenode	*parse_simple_command1(t_token *token_list)
{
	t_treenode	*node;
	t_treenode	*right;
	t_treenode	*left;

	if ((left = parse_word_node(token_list)) != NULL)
		return (NULL);
	if ((parse_redirection_node(token_list) != NULL))
		return (NULL);
	if ((right = parse_simple_command_node(token_list)))
		return (NULL);
	node = create_treenode(token_list->type, token_list->str);
	node->left = left;
	node->right = right;
	return (node);
}

t_treenode	*parse_simple_command2(t_token *token_list)
{
	t_treenode	*node;

	node = parse_word_node(token_list);
	return(node);
}

