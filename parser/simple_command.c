/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:29:26 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/02 14:49:49 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_simple_command_node(t_token **token_list);
t_treenode	*parse_simple_command1(t_token **token_list);
t_treenode	*parse_simple_command2(t_token **token_list);

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

t_treenode	*parse_simple_command_node(t_token **token_list)
{
	t_treenode	*node;
	t_token	*tmp = *token_list;

	if ((node = parse_simple_command1(token_list)))
	{
	//	token_list = tmp;
		return (node);
	}
	*token_list = tmp;
	if ((node = parse_simple_command2(token_list)))
	{
	//	token_list = tmp;
		return (node);
	}
	*token_list = tmp;
	return (NULL);
}

//no priorité ds les redirection, prio dans le sens de lecture (gauche à droite)
t_treenode	*parse_simple_command1(t_token **token_list)
{
	t_treenode	*node;
	t_treenode	*new_node;
	//t_treenode	*right;
	t_treenode	*left;

	if ((left = parse_word_node(token_list)) == NULL)
		return (NULL);
	//*token_list = (*token_list)->next;
	while ((new_node = parse_redirection_node(token_list)) != NULL)
	{
		//node = create_treenode(new_node->type, new_node->str);
		new_node->left = left;
		node = new_node;
		left = node;
		/*t_token *create_node = *token_list;
		*token_list = (*token_list)->next;
		if ((right = parse_simple_command_node(token_list)) == NULL)
			return (NULL);
		node = create_treenode(create_node->type, create_node->str);
		node->left = left;
		node->right = right;
		return (node);*/
	}
	return (node);
} 

t_treenode	*parse_simple_command2(t_token **token_list)
{
	t_treenode	*node;

	node = parse_word_node(token_list);
	return(node);
}

