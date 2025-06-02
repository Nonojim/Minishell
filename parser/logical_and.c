/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:27:49 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/02 17:20:50 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_logical_and_node(t_token **token_list);
t_treenode	*parse_logical_and1(t_token **token_list);
t_treenode	*parse_logical_and2(t_token **token_list);

//<line>                ::= 	<logical_or> (";" <logical_or>)* 1 
//							|	<logical_or> ";" 2 
//							|	<logical_or> 3 
//<logical_or>              ::= 	<logical_and> ("&&" <logical_and> )* 
//							|	<logical_or>
//<logical_and>              ::= 	<pipeline> ("||"  <pipeline> )* 
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

t_treenode	*parse_logical_and_node(t_token **token_list)
{
	t_token			*tmp = *token_list;
	t_treenode	*node = NULL;

	if ((node = parse_logical_and1(token_list)) != NULL)
		return (node);
	*token_list = tmp;
	//free_treenode(node);
	if ((node = parse_logical_and2(token_list)) != NULL)
		return (node);
	*token_list = tmp;
	//free_treenode(node);
	return (NULL);
}

//create_node = avant d'avancer dans la liste afin de créer le bon node (et pas le noeud suivant).
t_treenode	*parse_logical_and1(t_token **token_list)
{
	t_treenode	*left = NULL;
	t_treenode	*right = NULL;
	t_treenode	*node = NULL;

	if ((left = parse_pipeline_node(token_list)) == NULL)
		return (NULL);
	if (*token_list == NULL || (*token_list)->type != LOGICAL_AND)
	{
		//free_treenode(left);
		return (NULL);
	}
	t_token *create_node = *token_list;
	*token_list = (*token_list)->next;
	if ((right = parse_logical_and_node(token_list)) == NULL)
	{
		//free_treenode(left);
		return (NULL);
	}
	node = create_treenode(create_node->type, create_node->str);
	node->left = left;

	if (right->type == create_node->type) // si a droite se trouve un autre &&
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

t_treenode	*parse_logical_and2(t_token **token_list)
{
	t_treenode	*node = NULL;
	
	return (node = parse_pipeline_node(token_list));
}
