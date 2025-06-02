/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:30:57 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/02 10:40:20 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_word_node(t_token **token_list);
t_treenode	*parse_word1(t_token **token_list);

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

t_treenode	*parse_word_node(t_token **token_list)
{
	t_treenode	*node;
	t_token *tmp = *token_list;

	if ((node = parse_word1(token_list)))
	{
		//token_list = tmp;
		return (node);
	}
	*token_list = tmp;
	return (NULL);
}

t_treenode	*parse_word1(t_token **token_list)
{
	t_treenode *node;

	return (node = create_branch_words(token_list));
/*	t_treenode	*node;
	t_token *create_node = *token_list;
	//t_treenode *right;

	if (token_list == NULL || *token_list == NULL
		|| ((*token_list)->type != WORD
		&& (*token_list)->type != EXPANSION
		&& (*token_list)->type != SIMPLE_QUOTE
		&& (*token_list)->type != DOUBLE_QUOTE))
		return (NULL);
	create_node = *token_list;
	*token_list = (*token_list)->next;
	node = create_treenode(create_node->type, create_node->str);
 	if ((*token_list)->type == create_node->type && *token_list != NULL) // si a droite se trouve un autre &&
	{
		node->left = node;
		return (node->left);
	}
	else
	{
		node->right = NULL;
		node->left = NULL;
		return (node);
	}
	node->left = NULL;
	node->right = NULL;
	return (node);*/
}
