/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:29:26 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/28 11:40:41 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_simple_command_node(t_token *token_list);
t_treenode	*parse_simple_command1(t_token *token_list);
t_treenode	*parse_simple_command2(t_token *token_list); 

t_treenode	*parse_simple_command_node(t_token *token_list)
{
	t_treenode *node; 

	if (node = parse_simple_command1(token_list))
		return (node);
	if (node = parse_simple_command2(token_list))
		return (node);
	return (NULL);
}
//PARSE_COMMAND END

//PARSE_SIMPLE_COMMAND
t_treenode	*parse_simple_command1(t_token *token_list) 
// par de priorite entre redirection, prio se fait sens de lecture (gauche a droite)
{
	t_treenode *node;
	t_treenode *right;
	t_treenode *left;

	if (left = parse_simple_word_node(token_list) != NULL)
		return (NULL);
	if (parse_redirection_node(token_list) != NULL)
		return (NULL); 

// PAS SUR de devoir laisser celle la 
	if (right = parse_simple_command_node(token_list))
		return (NULL);
}
t_treenode	*parse_simple_command2(t_token *token_list)
{
	t_treenode *node;

	node = parse_simple_word_node(token_list);
	return(node);
}
//PARSE_SIMPLE_COMMAND END

