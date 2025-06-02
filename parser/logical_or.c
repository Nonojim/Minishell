/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_or.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:28:11 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/02 14:56:04 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_logical_or_node(t_token **token_list);
t_treenode	*parse_logical_or1(t_token **token_list);
t_treenode	*parse_logical_or2(t_token **token_list);

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

t_treenode	*parse_logical_or_node(t_token **token_list)
{
	t_token			*tmp = *token_list;
	t_treenode	*node;

	if ((node = parse_logical_or1(token_list)) != NULL)
	{
		return (node);
	}
		(*token_list) = tmp;
	if ((node = parse_logical_or2(token_list)) != NULL)
	{
		return (node);
	}
		(*token_list) = tmp;
	return (NULL);
}

t_treenode	*parse_logical_or1(t_token **token_list)
{
	t_treenode	*left;
	t_treenode	*right;
	t_treenode	*node;

	if ((left = parse_logical_and_node(token_list)) == NULL)
		return (NULL);

	if (*token_list == NULL || (*token_list)->type != LOGICAL_OR)
		return (NULL);
	t_token *create_node = *token_list;
	*token_list = (*token_list)->next;
	if ((right = parse_logical_or_node(token_list)) == NULL)
		return (NULL);
	node = create_treenode(create_node->type, create_node->str);
	node->left = left;
	if (right->type == create_node->type) // si a droite se trouve un autre ||
	{
		node->right = right->left;
		right->left = node;
		return (right);
	}
	else
	{
		node->right = right;
		return (node);
	}
}

t_treenode	*parse_logical_or2(t_token **token_list)
{
	t_treenode	*node;
	
	return (node = parse_logical_and_node(token_list));
}
