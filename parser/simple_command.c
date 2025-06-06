/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:29:26 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/06 20:10:46 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_simple_command_node(t_token **token_list);
t_treenode	*parse_simple_command1(t_token **token_list);
t_treenode	*parse_simple_command2(t_token **token_list);
t_treenode	*parse_simple_command3(t_token **token_list);

/*
 <simple_command>      ::= <word> ( <word> | <redirection> )*
												|	<word> <redirection> word
												|	<word>
*/
t_treenode	*parse_simple_command_node(t_token **token_list)
{
	t_treenode	*node = NULL;
	t_token		*tmp = *token_list;

	if ((node = parse_simple_command1(token_list)))
		return (node);
	*token_list = tmp;
	if ((node = parse_simple_command2(token_list)))
		return (node);
	*token_list = tmp;
	if ((node = parse_simple_command3(token_list)))
		return (node);
	*token_list = tmp;
	return (NULL);
}

//word _ redirection _ word
t_treenode	*parse_simple_command1(t_token **token_list)
{
	t_treenode	*node = NULL;
	t_treenode	*new_node = NULL;
	t_treenode	*left = NULL;

	if ((left = parse_word_node(token_list)) == NULL)
		return (NULL);
	//FAIT PEUT ETRE DISPARAITRE LES TOKEN
	while ((new_node = parse_redirection_node(token_list)) != NULL)
	{
		new_node->left = left;
		node = new_node;
		left = node;
	}
	if (node == NULL)
	{
		free_treenode(left);
		return (NULL);
	}
	return (node);
}

//redirection _ word
t_treenode	*parse_simple_command2(t_token **token_list)
{
	t_treenode	*node = NULL;
	t_treenode	*new_node = NULL;
	t_treenode	*left = NULL;

	if ((left = parse_word_node(token_list)) != NULL)
	{
		free_treenode(left);
		return (NULL);
	}
	t_token *tmp = *token_list;
	//FAIT PEUT ETRE DISPARAITRE LES TOKEN
	while((new_node = parse_redirection_node(token_list)) != NULL)
	{
		new_node->left = NULL;
		node = new_node;
	}
	if (node == NULL)
	{
		*token_list = tmp;
		free_treenode(left);
		return (NULL);
	}
	return (node);
}

//word
t_treenode	*parse_simple_command3(t_token **token_list)
{
	t_treenode	*node = NULL;
	node = parse_word_node(token_list); 
	if (*token_list != NULL && !is_word((*token_list)->type))
	{
		free_treenode(node);
		return (NULL);
	}
	return (node);
}
