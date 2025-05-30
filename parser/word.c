/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:30:57 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/30 13:51:40 by lduflot          ###   ########.fr       */
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
	t_treenode	*node;

	if (token_list == NULL || *token_list == NULL
		|| ((*token_list)->type != WORD
		&& (*token_list)->type != EXPANSION
		&& (*token_list)->type != SIMPLE_QUOTE
		&& (*token_list)->type != DOUBLE_QUOTE))
		return (NULL);
	node = create_treenode((*token_list)->type, (*token_list)->str);
	*token_list = (*token_list)->next;
	return (node);
}
