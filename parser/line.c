/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:27:07 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/29 16:27:54 by lduflot          ###   ########.fr       */
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

t_treenode	*parse_line_node(t_token **token_list);
t_treenode	*parse_line1(t_token **token_list);
t_treenode	*parse_line2(t_token **token_list);
t_treenode	*parse_line3(t_token **token_list);

t_treenode	*parse_line_node(t_token **token_list)
{
	t_token			*tmp = *token_list;
	t_treenode	*node;

	if ((node = parse_line1(token_list)) != NULL)
	{
		//token_list = tmp;
		return (node);
	}
	*token_list = tmp;
	if ((node = parse_line2(token_list)) != NULL)
	{
		//token_list = tmp;
		return (node);
	}
	*token_list = tmp;
	if ((node = parse_line3(token_list)) != NULL)
	{
		//token_list = tmp;
		return (node);
	}
	*token_list = tmp;
	return (NULL);
}

t_treenode	*parse_line1(t_token **token_list)
{
	t_treenode	*left;
	t_treenode	*right;
	t_treenode	*node;

	if ((left = parse_logical_and_node(token_list)) == NULL)
	{
		printf("entre first");
		return (NULL);
	}
	if ((*token_list)->type != SEMICOLON)
	{
		printf("entre second");
		return (NULL);
	}
	*token_list = (*token_list)->next;
	if ((right = parse_line_node(token_list)) == NULL)
	{
		printf("entre 3");
		return (NULL);
	}
	node = create_treenode(SEMICOLON, ";");
//	create_branch_words(token_list);
	node->left = left;
	node->right = right;
	return (node);
}

t_treenode	*parse_line2(t_token **token_list)
{
	t_treenode	*left;
	t_treenode	*node;

	if ((left = parse_logical_and_node(token_list)) == NULL)
	return (NULL);
	if ((*token_list)->type != SEMICOLON)
		return (NULL);
	*token_list = (*token_list)->next;
	node = create_treenode(SEMICOLON, ";");
	//node =create_branch_words(token_list);
	node->left = left;
	node->right = NULL;
	return (node);
}

t_treenode	*parse_line3(t_token **token_list)
{
	t_treenode	*node;

	return (node = parse_logical_and_node(token_list));
}
