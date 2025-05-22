/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:39:19 by npederen          #+#    #+#             */
/*   Updated: 2025/05/21 18:13:16 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "../minishell.h"
# include "../includes/tokenizer.h"

/*
 * Grammaire LL : va definir la structure syntaxique d'une ligne de commande Shell.
 * Begin rule line.
 * Structure adapte a un parseur descendant recursif. 
 * L'AST va être construit à partir de la grammaire, chaque regle de grammaire correspond a un type de noeud AST.
 
 ** Symbole dans la grammaire (notation EBNF)
 ::= == opérateur d'affectation de règle, "est définit comme"
 | (ou alternatif) == l'élement peut être l'un ou l'autre
 * == peut apparaitre plusieurs fois ou zéro fois
 + == plusieurs fois ou 1 fois minimum
 ? == zéro ou 1 fois
 
 **  exemple = echo "Hello" && ls -l ; echo test
 * echo = WORD, "Hello" = WORD, && = LOGICAL_AND, ls = WORD, -l = WORD ; = SEMICOLON, echo = WORD test = WORD

 Grammaire LL - Symbole token

<line>                ::= <command_sequence> (";" <command_sequence>)*
<command_sequence>    ::= <and_or>
<and_or>              ::= <pipeline> ( ("&&" | "||") <pipeline> )*
<pipeline>            ::= <command> ( "|" <command> )*
<command>             ::= "(" <line> ")" | <simple_command>
<simple_command>      ::= <word> ( <word> | <redirection> )*
<redirection>         ::= ( "<" | "<<" | ">" | ">>" )+ <word>
<word>                ::= /* token representing a word 

line           ::= command_sequence (SEMICOLON command_sequence)*
command_sequence ::= and_or ;
and_or         ::= pipeline ( (LOGICAL_AND | LOGICAL_OR) pipeline )* ;
pipeline       ::= command ( PIPE command )* ;
command        ::= (BRACKETS_L line BRACKETS_R) | simple_command ;
simple_command ::= WORD ( WORD | redirection )* ;
redirection    ::= (INPUT_REDIRECTION | HERE_DOCUMENT
				   OUTPUT_REDIRECTION | APPEND_OUTPUT_REDIRECTION)+ WORD ;
*/

typedef struct s_treenode
{
	int					type;
	char				*str;
	struct s_treenode	*right;
	struct s_treenode	*left;
}			t_treenode;

enum e_DIRECTION
{
	LEFT, //0
	RIGHT, //1
};

//Utils / Init AST
void	astreeprint(t_treenode* node, int depth);
void	print_indent(int depth);
t_treenode	*create_treenode(int type, char *str);
void	add_node(t_treenode *parent_node, t_treenode *new_child, int dir);
void	free_treenode(t_treenode *treenode);
t_treenode	*create_branch_words(t_token **token_list);

//Parse
t_treenode	*create_tree(t_token *token_list);
t_treenode	*create_branch_words(t_token **token_list);

#endif
