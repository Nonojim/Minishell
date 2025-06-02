/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:29:59 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/02 17:22:03 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

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


t_treenode	*parse_command_node(t_token **token_list);
t_treenode	*parse_command_node1(t_token **token_list);
t_treenode	*parse_command_node2(t_token **token_list);


// Ne fonctionne pas,
t_treenode	*parse_command_node(t_token **token_list)
{
	t_token *tmp = *token_list;
	t_treenode	*node = NULL;

	if ((node = parse_command_node1(token_list)))
		return (node);
	*token_list = tmp;
	//free_treenode(node);
	if ((node = parse_command_node2(token_list)))
		return (node);
	*token_list = tmp;
	//free_treenode(node);
	return (NULL);
}

//Passe sur la brackets_R ok repasse dans parse_line
//Sauf que une fois que tout ce qui est a l'intérieur a été parsé on revient dans parse_command_node1 et return null sur bracket_R
// donc on token jamais la bracket_L
// Maybe faire 2 fonction une qui parse la bracket_R une qui parse la bracket_L
t_treenode	*parse_command_node1(t_token **token_list)
{
	t_treenode	*node = NULL;
	t_treenode	*node2 = NULL;
	//t_treenode	*left;
	t_treenode	*right = NULL;

	if (*token_list == NULL || (*token_list)->type != BRACKETS_R)
		return (NULL);
//	t_token *create_node = *token_list;
	*token_list = (*token_list)->next;
	if ((right = parse_line_node(token_list)) == NULL)
		return (NULL);
	if (*token_list == NULL || (*token_list)->type != BRACKETS_L)
	{
		//free_treenode(right);
		return (NULL);
	}
	if ((*token_list)->type == BRACKETS_L)
	{
		node2 = create_treenode(BRACKETS_L, ")");
		return (node2);
	}
	//t_token *create_node = *token_list;
	//*token_list = (*token_list)->next;
	if ((right = parse_command_node1(token_list)) != NULL)
	{
		//free_treenode(right);
	//	free_treenode(node2);
		return (NULL);
	}
	node = create_treenode(BRACKETS_R, "(");
	//node->left = NULL;
	node->right = right;
	return (node);
}

t_treenode	*parse_command_node2(t_token **token_list)
{
	t_treenode	*node = NULL;

	return (node = parse_simple_command_node(token_list));
}
