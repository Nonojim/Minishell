/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:45:33 by npederen          #+#    #+#             */
/*   Updated: 2025/06/11 14:40:14 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void		astreeprint(t_treenode *node, int depth);
void		print_indent(int depth);
t_treenode	*create_treenode(int type, char *str);
void		add_node(t_treenode *parent_node, t_treenode *new_child, int dir);
void		free_treenode(t_treenode *treenode);
t_treenode	*create_branch_words(t_token **token_list);


int	is_redirection(int type)
{
	return (type == INPUT_REDIRECTION
		|| type == OUTPUT_REDIRECTION
		|| type == HERE_DOCUMENT
		|| type == APPEND_OUTPUT_REDIRECTION);
}
/*
A FAIRE !!!! 
Gérer dans le tokenizer (a(b)c) = ouvre une readline = incorrect;
Modifier la priorité des pipe sur les redirection dans le code (mais grammaire bonne)
Gerer les leaks
Normer (good luck)
*/

// Manque dans la grammaire = token simple_quote et double_quote ; token_expansion

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
