/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:27:07 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/02 17:21:26 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/*
CE QUI NE FONCTIONNE PAS
tout les noeuds ce crée à droite au lieu de gauche
Pas d'AST si = bracket; expansion; redirection; plusieurs word côte à côte
Verifier entre || et && qui s'exe en first
Mauvais ordre dans les noeuds
Minishell$ test && test | test
[0 : test] -> [3 : &&] -> [0 : test] -> [1 : |] -> [0 : test] -> NULL
Node type: 3, data: "&&"
Left:
  Node type: 0, data: "test"
Right:
  Node type: 1, data: "|"
  Left:
    Node type: 0, data: "test"
  Right:
    Node type: 0, data: "test"
Minishell$ 

*/


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


t_treenode	*parse_line_node(t_token **token_list);
t_treenode	*parse_line1(t_token **token_list);
t_treenode	*parse_line2(t_token **token_list);
t_treenode	*parse_line3(t_token **token_list);

t_treenode	*parse_line_node(t_token **token_list)
{
	t_token			*tmp = *token_list;
	t_treenode	*node = NULL;

	if ((node = parse_line1(token_list)) != NULL)
		return (node);
	*token_list = tmp;
	//free_treenode(node);
	if ((node = parse_line2(token_list)) != NULL)
		return (node);
	*token_list = tmp;
	free_treenode(node);
	if ((node = parse_line3(token_list)) != NULL)
		return (node);
	*token_list = tmp;
//	free_treenode(node);
	return (NULL);
}

t_treenode	*parse_line1(t_token **token_list)
{
	t_treenode	*left = NULL;
	t_treenode	*right = NULL;
	t_treenode	*node = NULL;

	if ((left = parse_logical_or_node(token_list)) == NULL)
		return (NULL);
	if (*token_list == NULL || (*token_list)->type != SEMICOLON)
	{
		//printf("qui free: %p - %s\n", left, left->str);
		//free_treenode(left);
		return (NULL);
	}
	*token_list = (*token_list)->next;
	if ((right = parse_line_node(token_list)) == NULL)
	{
		//printf("qui free: %p - %s\n", left, left->str);
		//free_treenode(left);
		return (NULL);
	}
	node = create_treenode(SEMICOLON, ";");
	node->left = left;
	node->right = right;
	return (node);
}

t_treenode	*parse_line2(t_token **token_list)
{
	t_treenode	*left = NULL;
	t_treenode	*node = NULL;

	if ((left = parse_logical_or_node(token_list)) == NULL)
		return (NULL);
	if (*token_list == NULL || (*token_list)->type != SEMICOLON)
	{
		//free_treenode(left);
		return (NULL);
	}
	*token_list = (*token_list)->next;
	node = create_treenode(SEMICOLON, ";");
	//node =create_branch_words(token_list);
	node->left = left;
	node->right = NULL;
	return (node);
}

t_treenode	*parse_line3(t_token **token_list)
{
	t_treenode	*node = NULL;

	return (node = parse_logical_or_node(token_list));
}
