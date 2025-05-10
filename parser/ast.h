/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:39:19 by npederen          #+#    #+#             */
/*   Updated: 2025/05/10 11:17:38 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "../minishell.h"

/*
Grammaire LL - Symbole token

line           ::= and_or ( ";" and_or )* ;
and_or         ::= pipeline ( ("&&" | "||") pipeline )* ;
pipeline       ::= command ( "|" command )* ;
command        ::= "(" line ")" | simple_command ;
simple_command ::= word ( word | redirection )* ;
redirection    ::= ( "<" | "<<" | ">" | ">>" ) word ;
word            ::= un mot brut ou une chaîne entre guillemets

Grammaire LL - Token name

line           ::= and_or ( SEMICOLON and_or )* ;
and_or         ::= pipeline ( (LOGICAL_AND | LOGICAL_OR) pipeline )* ;
pipeline       ::= command ( PIPE command )* ;
command        ::= (BRACKETS_R line BRACKETS_L) | simple_command ;
simple_command ::= WORD ( WORD | redirection )* ;
redirection    ::= (INPUT_REDIRECTION | HERE_DOCUMENT
									| OUTPUT_REDIRECTION | APPEND_OUTPUT_REDIRECTION) WORD ;
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
	LEFT,
	RIGHT,
};

#endif
