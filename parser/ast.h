/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:39:19 by npederen          #+#    #+#             */
/*   Updated: 2025/06/16 18:48:42 by npederen         ###   ########.fr       */
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
 * echo = WORD, "Hello" = WORD, && = logical_and, ls = WORD, -l = WORD ; = SEMICOLON, echo = WORD test = WORD

 Grammaire LL - Symbole token

//<line>                ::= 	<logical_or> (";" <logical_or>)* 1
//							|	<logical_or> ";" 2
//							|	<logical_or> 3
//<logical_or>              ::= 	<logical_and> ("&&" <logical_and> )*
//							|	<logical_and>
//<logical_and>              ::= 	<pipeline> ("||"  <pipeline> )*
//							|	<pipeline>
//<pipeline>            ::= <command> ( "|" <command> )*
//							|	<command> "|" <command>
//							|	<commandet
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
//							| NULL*/

typedef struct s_treenode
{
	int					type;
	char				**argv;
	char				*str;
	struct s_treenode	*right;
	struct s_treenode	*left;
}	t_treenode;

enum e_NODE
{
	SUBSHELL
};

enum e_DIRECTION
{
	LEFT, // 0
	RIGHT, // 1
};

// Utils / Init AST
void		astreeprint(t_treenode *node, int depth);
void		print_indent(int depth);
void		add_node(t_treenode *parent_node, t_treenode *new_child, int dir);
void		free_treenode(t_treenode *node);
t_treenode	*create_branch_words(t_token **tokens);
t_treenode	*create_treenode(int type, char *str);
int			is_redirection(int type);
int			is_word_type(int type);
int			is_op_logique(int type);
int			is_bracket(int type);
t_treenode	*free_settoken_thenreturn(t_treenode *nodetofree,
				t_token **tokenstoset, t_token *setting);
t_treenode	*printerror_then_return_null(t_token **tokens);
t_treenode	*free_then_return_null(t_treenode *left);

// Parse
t_treenode	*create_tree(t_token *tokens);
t_treenode	*create_branch_words(t_token **tokens);

// LINE
t_treenode	*parse_line_node(t_token **tokens);
t_treenode	*parse_line1(t_token **tokens);

t_treenode	*parse_line2(t_token **tokens);
t_treenode	*parse_line3(t_token **tokens);

// Logical_and
t_treenode	*parse_logical_and_node(t_token **tokens);
t_treenode	*parse_logical_and1(t_token **tokens);

// Logical_or
t_treenode	*parse_logical_or_node(t_token **tokens);
t_treenode	*parse_logical_or1(t_token **tokens);

// Pipeline
t_treenode	*parse_pipeline_node(t_token **tokens);
t_treenode	*parse_pipeline1(t_token **tokens);
t_treenode	*parse_pipeline2(t_token **tokens);

// Command
t_treenode	*parse_command_node(t_token **tokens);
t_treenode	*parse_command_node1(t_token **tokens);
t_treenode	*parse_command_node2(t_token **tokens);
t_treenode	*parse_command_node3(t_token **tokens);
t_treenode	*parse_command_node4(t_token **tokens);
t_treenode	*parse_command_node5(t_token **tokens);

// Simple_command
t_treenode	*parse_simple_command_node(t_token **tokens);
t_treenode	*parse_simple_command1(t_token **tokens);
t_treenode	*parse_simple_command2(t_token **tokens);

// Redirection
t_treenode	*parse_redirection_node(t_token **tokens);
t_treenode	*parse_redirection1(t_token **tokens);
t_treenode	*parse_redirection2(t_token **tokens);

// WORD
t_treenode	*parse_word_node(t_token **tokens);
t_treenode	*parse_word1(t_token **tokens);

int			parse_error(int state);
void		print_error(t_token *tokens);

#endif
