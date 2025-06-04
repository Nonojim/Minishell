/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:29:59 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/04 20:54:47 by lduflot          ###   ########.fr       */
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
//							| simple_command "(" <line> ")"
//							|"(" <line> ")" simple_command
//							|simple_command "(" <line> ")" simple_command
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
t_treenode	*parse_command_node3(t_token **token_list);
t_treenode	*parse_command_node4(t_token **token_list);
t_treenode	*parse_command_node5(t_token **token_list);


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
	if ((node = parse_command_node3(token_list)))
		return (node);
	*token_list = tmp;
	//free_treenode(node);
	if ((node = parse_command_node4(token_list)))
		return (node);
	*token_list = tmp;
	//free_treenode(node);
	if ((node = parse_command_node5(token_list)))
		return (node);
	*token_list = tmp;
	//free_treenode(node);
	return (NULL);
}

//Passe sur la brackets_R ok repasse dans parse_line
//Sauf que une fois que tout ce qui est a l'intérieur a été parsé on revient dans parse_command_node1 et return null sur bracket_R
// donc on token jamais la bracket_L
// Maybe faire 2 fonction une qui parse la bracket_R une qui parse la bracket_L

// 	"(" <line> ")"
t_treenode	*parse_command_node1(t_token **token_list)
{
	t_treenode	*node = NULL;
	t_token	*tmp;
	t_treenode	*right = NULL;
	t_treenode	*left = NULL;
	
	if ((left = parse_simple_command_node(token_list)) != NULL)
		return (NULL);

	if (*token_list == NULL || (*token_list)->type != BRACKETS_R)
		return (NULL);

	tmp = *token_list;
	*token_list = (*token_list)->next;

	while ((*token_list)->type != BRACKETS_L && *token_list != NULL)
	{
		*token_list = (*token_list)->next;
	}
	if ((*token_list)->type == BRACKETS_L && *token_list != NULL)
	{
		*token_list = tmp;
		node = create_treenode(SUBSHELL, "()");
		*token_list = (*token_list)->next;
		node->left = parse_line_node(token_list);
		if (node->left == NULL)
			return(NULL);	
		if (*token_list == NULL || (*token_list)->type != BRACKETS_L)
			return (NULL);
		
		*token_list = (*token_list)->next;
		if ((right = parse_simple_command_node(token_list)) != NULL)
			return (NULL);
		//node->right = NULL;
		return (node);
	}
	else
	{
		*token_list = tmp;
		*token_list = (*token_list)->next;
		return (NULL);
	}
}

//simple_command "(" <line> ")"
t_treenode	*parse_command_node2(t_token **token_list)
{
	t_treenode	*node = NULL;
	t_token			*tmp;
	t_treenode	*left = NULL;
	t_treenode *right = NULL;


	if ((left = parse_simple_command_node(token_list)) == NULL)
		return (NULL);
	if (*token_list == NULL || (*token_list)->type != BRACKETS_R)
		return (NULL);

	tmp = *token_list;
	*token_list = (*token_list)->next;

	while ((*token_list)->type != BRACKETS_L && *token_list != NULL)
		*token_list = (*token_list)->next;

	if ((*token_list)->type == BRACKETS_L && *token_list != NULL)
	{
		*token_list = tmp;
		node = create_treenode(SUBSHELL, "()");
		*token_list = (*token_list)->next;

		node->right = parse_line_node(token_list);
		if (node->right == NULL)
			return(NULL);
		if (*token_list == NULL || (*token_list)->type != BRACKETS_L)
			return (NULL);
	
		*token_list = (*token_list)->next;
		if ((right = parse_simple_command_node(token_list)) != NULL)
			return (NULL);
		node->left = left;
		//node->right = NULL;
		//node->right = new_node;
		//node->right = new_node;
		return (node);
	}
	else
	{
		*token_list = tmp;
		*token_list = (*token_list)->next;
		return (NULL);
	}
}

//"(" <line> ")" simple_command
t_treenode	*parse_command_node3(t_token **token_list)
{
		t_treenode	*node = NULL;
	t_token	*tmp;
	//t_treenode	*left = NULL;
	t_treenode	*right = NULL;

//	if ((left = parse_simple_command_node(token_list)) != NULL)
	//	return (NULL);

	if (*token_list == NULL || (*token_list)->type != BRACKETS_R)
		return (NULL);

	tmp = *token_list;
	*token_list = (*token_list)->next;

	while ((*token_list)->type != BRACKETS_L && *token_list != NULL)
		*token_list = (*token_list)->next;

	if ((*token_list)->type == BRACKETS_L && *token_list != NULL)
	{
		*token_list = tmp;
		node = create_treenode(SUBSHELL, "()");
		*token_list = (*token_list)->next;
		node->left = parse_line_node(token_list);

		if (node->left == NULL)
			return(NULL);
		
		if (*token_list == NULL || (*token_list)->type != BRACKETS_L)
			return (NULL);
	
		*token_list = (*token_list)->next;
		if ((right = parse_simple_command_node(token_list)) == NULL)
			return (NULL);
		//node->left = left;
		node->right = right;
		//node->right = new_node;
		return (node);
	}
	else
	{
		*token_list = tmp;
		*token_list = (*token_list)->next;
		return (NULL);
	}
}

//simple_command "(" <line> ")" simple_command
t_treenode	*parse_command_node4(t_token **token_list)
{
	t_treenode	*node = NULL;
	t_token	*tmp;
	t_treenode	*left = NULL;
	t_treenode	*right = NULL;

	if ((left = parse_simple_command_node(token_list)) == NULL)
		return (NULL);

	if (*token_list == NULL || (*token_list)->type != BRACKETS_R)
		return (NULL);

	tmp = *token_list;
	*token_list = (*token_list)->next;

	while ((*token_list)->type != BRACKETS_L && *token_list != NULL)
		*token_list = (*token_list)->next;

	if ((*token_list)->type == BRACKETS_L && *token_list != NULL)
	{
		*token_list = tmp;
		node = create_treenode(SUBSHELL, "()");
		*token_list = (*token_list)->next;

		node->right = parse_line_node(token_list);
		if (node->right == NULL)
			return(NULL);
		if (*token_list == NULL || (*token_list)->type != BRACKETS_L)
			return (NULL);
	
		*token_list = (*token_list)->next;
		if ((right = parse_simple_command_node(token_list)) == NULL)
			return (NULL);
		node->left = left;
		node->right = right;
		//node->right = NULL;
		//node->right = new_node;
		//node->right = new_node;
		return (node);
	}
	else
	{
		*token_list = tmp;
		*token_list = (*token_list)->next;
		return (NULL);
	}
}

//simple_command
t_treenode	*parse_command_node5(t_token **token_list)
{
	t_treenode	*node = NULL;

	return (node = parse_simple_command_node(token_list));
}
