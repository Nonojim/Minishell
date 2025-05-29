/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:29:59 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/29 13:24:39 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

//<line>                ::= 	<logical_and> (";" <logical_and>)* 1 
//							|	<logical_and> ";" 2 
//							|	<logical_and> 3 
//<logical_and>              ::= 	<logical_or> ("&&" <logical_or> )* 
//							|	<logical_or>
//<logical_or>              ::= 	<pipeline> ("||"  <pipeline> )* 
//							|	<pipeline>
//<pipeline>            ::= <command> ( "|" <command> )*
//							|	<command> "|" <command>
//							|	<command>
//<command>             ::= "(" <line> ")" | <simple_command>
//							|	"(" <line> ")"
//							|	<simple_command>
//<simple_command>      ::= <word> ( <word> | <redirection> )*
//							|	<word> <redirection> word
//							|	<word>
//<redirection>         ::= ( "<" | "<<" | ">" | ">>" ) <word>
//							|	">" <word>
//							|	">>" <word>
//							|	"<" <word>
//							|	"<<" <word>
//<word>          ::= [WORD token]
//							| NULL

t_treenode	*parse_command_node(t_token **token_list);
t_treenode	*parse_command_node1(t_token **token_list);
t_treenode	*parse_command_node2(t_token **token_list);

t_treenode	*parse_command_node(t_token **token_list)
{
	t_token *tmp = *token_list;
	t_treenode	*node;

	if ((node = parse_command_node1(token_list)))
		return (node);
	*token_list = tmp;
	if ((node = parse_command_node2(token_list)))
		return (node);
	*token_list = tmp;
	return (NULL);
}

t_treenode	*parse_command_node1(t_token **token_list)
{
	t_treenode	*node;
	//t_treenode	*left;
	t_treenode	*right;

	if ((*token_list)->type != BRACKETS_L)
		return (NULL);
	if ((right = parse_line_node(token_list)) != NULL)
		return (NULL);
	if ((*token_list)->type != BRACKETS_R)
		return (NULL);
	*token_list = (*token_list)->next;
	if ((right = parse_command_node1(token_list)) != NULL)
		return (NULL);
	node = create_treenode((*token_list)->type, (*token_list)->str);
	//node->left = NULL;
	node->right = right;
	return (node);
}

t_treenode	*parse_command_node2(t_token **token_list)
{
	t_treenode	*node;

	return (node = parse_simple_command_node(token_list));
}
