/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:28:49 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/29 23:12:35 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_redirection_node(t_token **token_list);
t_treenode	*parse_redirection1(t_token **token_list);
//t_treenode	*parse_redirection2(t_token *token_list);

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

t_treenode	*parse_redirection_node(t_token **token_list)
{
	t_treenode	*node;
	t_token *tmp = *token_list;

	if ((node = parse_redirection1(token_list)) != NULL)
	{
	//	token_list = tmp;
		return (node);
	}
	*token_list = tmp;
	//if ((node = parse_redirection2(token_list))) 
		//return (node);
	
	return (NULL);
}
t_treenode	*parse_redirection1(t_token **token_list)
{
	t_treenode	*node;
	t_treenode	*right;
//	t_treenode	*left;

	if (*token_list == NULL)
		return (NULL);
	if((*token_list)->type != INPUT_REDIRECTION &&
		(*token_list)->type != OUTPUT_REDIRECTION &&
		(*token_list)->type != HERE_DOCUMENT &&
		(*token_list)->type != APPEND_OUTPUT_REDIRECTION)
		return (NULL);
	t_token *create_node = *token_list;
	*token_list = (*token_list)->next;
	if ((right = parse_word_node(token_list)) != NULL)
		return (NULL);
	node = create_treenode(create_node->type, create_node->str);
//	node->left = NULL;
	node->right = right;
	return (node);
}
