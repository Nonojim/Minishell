/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:29:59 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/10 20:46:43 by lduflot          ###   ########.fr       */
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
		|| type == SEMICOLON
		|| type == BRACKETS_R);
}

// "(" <line> ")" redirection
t_treenode	*parse_command_node1(t_token **token_list)
{
t_token		*tmp = *token_list;
	t_treenode	*node; //contenu du sous_shell
	t_treenode	*redir_node; //stock redirection trouver aprés parenthese

	if (*token_list == NULL || (*token_list)->type != BRACKETS_L)
		return (NULL);

	*token_list = (*token_list)->next; // on mange la bracket_L 

	node = parse_line_node(token_list); // parse int subshell
	if (node == NULL || *token_list == NULL || (*token_list)->type != BRACKETS_R)
	{
		free_treenode(node);
		*token_list = tmp;
		return (NULL);
	}
	*token_list = (*token_list)->next; // on mange bracket_R
	t_treenode *subshell_node = create_treenode(SUBSHELL, "()");
	subshell_node->left = node; //contient commande subshell	
	tmp = *token_list;
//	printf("%p\n", (*token_list)->str);
	while ((redir_node = parse_redirection_node(token_list)) != NULL)
	{
		redir_node->left = subshell_node;
		subshell_node = redir_node;
	}
	if (*token_list != NULL && !operator_or_nothing_before_subshell((*token_list)->type) && !is_redirection((*token_list)->type))
	{
		free_treenode(node);
		*token_list = tmp;
		return (NULL);
	}
	return (subshell_node);
}

//simple_command
t_treenode	*parse_command_node2(t_token **token_list)
{
	t_treenode	*node;

	node  = parse_simple_command_node(token_list);
	return (node);

}
