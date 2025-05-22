/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root.c                                              :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:45:33 by npederen          #+#    #+#             */
/*   Updated: 2025/05/21 18:09:21 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	astreeprint(t_treenode* node, int depth);
void	print_indent(int depth);
t_treenode	*create_treenode(int type, char *str);
void	add_node(t_treenode *parent_node, t_treenode *new_child, int dir);
void	free_treenode(t_treenode *treenode);
t_treenode	*create_branch_words(t_token **token_list);

//<line>                ::= 	<and_or> (";" <and_or>)* 1 
//							|	<and_or> ";" 2 
//							|	<and_or> 3 
//<and_or>              ::= 	<pipeline> ( ("&&" | "||") <pipeline> )* 
//							|	<pipeline> "&&" <pipeline>
//							|	<pipeline> "||" <pipeline>
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

/*
* Problematique du code : pointeur trees certainement,
lorsaue node right = bouger token_list ? 
Liste circulaire double chaine = maybe dans le tokenizer ? en reflexion
* Modifier le tokenizer = quote,&& || sans arg 
*/
t_treenode *parse_and_or_node(t_token *token_list)
{
	t_token *tmp = token_list;
	t_treenode *node;

	if (node = parse_and_or_node1(&token_list) != NULL)
		return (node);
	if (node = parse_and_or_node2(&token_list) != NULL)
		return (node);
	if (node = parse_and_or_node3(&token_list) != NULL)
		return (node);
	if (node = parse_and_or_node4(&token_list) != NULL)
		return (node);
	return (NULL);
} 
t_treenode *parse_and_or_node1(t_token *token_list)
{
	t_treenode *left;
	t_treenode *right;
	t_treenode *node;
	//t_treenode *result;

	if (left = parse_pipeline(token_list) == NULL)
		return (NULL);
	if (token_list->type != LOGICAL_AND || token_list->type != LOGICAL_OR)
		return (NULL);
	if (right = parse_line(token_list) == NULL)
		return (NULL);
	node = create_branch_words(token_list->type);
	node->left = left;
	node->rigt = right;
	return (node);
}
t_treenode *parse_and_or_node2(t_token *token_list)
{

}
t_treenode *parse_and_or_node3(t_token *token_list)
{

}
t_treenode *parse_and_or_node4(t_token *token_list)
{

}


t_treenode *parse_line_node(t_token *token_list)
{
	t_token *tmp = token_list;
	t_treenode *node;

	if (node = parse_line1(&token_list) != NULL)
		return (node);
	if (node = parse_line2(&token_list) != NULL)
		return (node);
	if (node = parse_line3(&token_list) != NULL)
		return (node);
	return (NULL);
}

t_treenode	*parse_line1(t_token *token_list)
{
	t_treenode *left;
	t_treenode *right;
	t_treenode *node;
	//t_treenode *result;

	if (left = parse_and_or(token_list) == NULL)
		return (NULL);
	if (token_list->type != SEMICOLON)
		return (NULL);
	
	if (right = parse_line(token_list) == NULL)
		return (NULL);
	node = create_branch_words(token_list->type);
	node->left = left;
	node->rigt = right;
	return (node);
}

t_treenode	*parse_line2(t_token *token_list)
{
	t_treenode *left;
	t_treenode *node;

	if (left = parse_and_or(token_list) == NULL)
		return (NULL);
	if(token_list->type != SEMICOLON)
		return (NULL);
	if(token_list->next->type != NULL)
		return (NULL);
	node = create_branch_words(token_list->type);
	node->left = left;
	node->right = NULL;
	return (node);
}
t_treenode	*parse_line3(t_token *token_list)
{
	t_treenode *left;
	t_treenode *right;

	if (token_list->type != SEMICOLON)
		return (NULL);
	if (right = parse_and_or(tmp) != NULL)
		return (node)
	node = create_branch_words(token_list->type);
	node->left = left;
	node->right = right;
	return (node);
}
t_treenode	*parse_pipeline(void);
t_treenode	*parse_command(void);
t_treenode	*parse_simple_command(void);
t_treenode	*parse_redirection(void);