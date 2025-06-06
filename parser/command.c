/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:29:59 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/06 20:10:38 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_command_node(t_token **token_list);
t_treenode	*parse_command_node1(t_token **token_list);
t_treenode	*parse_command_node2(t_token **token_list);

/*
<command>     ::= "(" <line> ")" | <simple_command>
							|	"(" <line> ")" 
							| "(" <line> ")" redirection
							|	<simple_command>
*/

t_treenode	*parse_command_node(t_token **token_list)
{
	t_token		*tmp;
	t_treenode	*node;

	tmp = *token_list;
	node = NULL;
	node = parse_command_node1(token_list);
	if (node)
		return (node);
	*token_list = tmp;
	node = parse_command_node2(token_list);
	if (node)
		return (node);
	*token_list = tmp;

	return(NULL);
}

int	operator_or_nothing_before_subshell(int type)
{
	return(type == LOGICAL_AND
		|| type == LOGICAL_OR
		|| type == PIPE
		|| type == SEMICOLON);
}

// "(" <line> ")" redirection
t_treenode	*parse_command_node1(t_token **token_list)
{
	t_treenode	*node;
	t_token		*tmp;
	
	node = NULL;
	tmp = *token_list;
	if (*token_list == NULL || (*token_list)->type != BRACKETS_L)
		return (NULL);
	tmp = *token_list;
	while ((*token_list)->type != BRACKETS_R && *token_list != NULL)
		*token_list = (*token_list)->next;
	if (*token_list == NULL || (*token_list)->type != BRACKETS_R)
	{
		*token_list = tmp;
		return (NULL);
	}
	*token_list = tmp;
	node = create_treenode(SUBSHELL, "()");
	if (!node)
		return (NULL);
	*token_list = (*token_list)->next;
	node->left = parse_line_node(token_list);
	if (node->left == NULL || *token_list == NULL)
	{
		free_treenode(node);
		return (NULL);
  }
	*token_list = (*token_list)->next;
	t_token	*tmp2 = *token_list;
	t_treenode *node_redir;
	//FAIT DISPARAITRE LES TOKEN
	while((node_redir = parse_redirection_node(token_list)) != NULL)
	{
		node_redir->left = node;
		node = node_redir;
	}
	if (*token_list != NULL && !operator_or_nothing_before_subshell((*token_list)->type) && !is_redirection((*token_list)->type))
	{
		free_treenode(node);
		*token_list = tmp2;
		return (NULL);
	}
	if (node_redir != NULL)
	{
		free_treenode(node_redir);
	}
	return (node);
}

//simple_command
t_treenode	*parse_command_node2(t_token **token_list)
{
	t_treenode	*node;

	node  = parse_simple_command_node(token_list);
	return (node);

}