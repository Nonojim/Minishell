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

//PARSE_LINE_NODE 
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

	if (left = parse_and_or(token_list) == NULL)
		return (NULL);

	if (token_list->type != SEMICOLON)
		return (NULL);
	
	if (right = parse_line(token_list) == NULL)
		return (NULL);
	node = create_treenode(token_list->type, token_list->str);
	node->left = left;
	node->right = right;
	return (node);
}

t_treenode	*parse_line2(t_token *token_list)
{
	t_treenode *left;
	t_treenode *node;

	if (left = parse_and_or(token_list) == NULL)
	return (NULL);

	if (token_list->type != SEMICOLON)
		return (NULL);

	node = create_treenode(token_list->type, token_list->str);
	node->left = left;
	node->right = NULL;
	return (node);
}

t_treenode	*parse_line3(t_token *token_list)
{
	t_treenode *node;

	return (node = parse_logical_and_node(token_list));
}
//PARSE_LINE_NODE END

//PARSE_LOGICAL_AND
t_treenode *parse_logical_and_node(t_token *token_list)
{
	t_token *tmp = token_list;
	t_treenode *node;

	if (node = parse_logical_and1(&token_list) != NULL)
		return (node);
	if (node = parse_logical_and2(&token_list) != NULL)
		return (node);
	return (NULL);
} 
t_treenode *parse_logical_and1(t_token *token_list)
{
	t_treenode *left;
	t_treenode *right;
	t_treenode *node;

	if (left = parse_logical_or_node(token_list) == NULL)
		return (NULL);

	if (token_list->type != LOGICAL_AND)
		return (NULL);
		
	if (right = parse_logical_and_node(token_list) == NULL)
		return (NULL);
	node = create_treenode(token_list->type, token_list->str);
	node->left = left;
	node->right = right;
	return (node);
}
t_treenode *parse_logical_and2(t_token *token_list)
{
	t_treenode *node;
	
	return (node = parse_logical_or_node(token_list));
}
//PARSE_LOGICAL_AND END

//PARSE_LOGICAL_OR
t_treenode *parse_logical_or_node(t_token *token_list)
{
	t_token *tmp = token_list;
	t_treenode *node;

	if (node = parse_logical_or1(&token_list) != NULL)
		return (node);
	if (node = parse_logical_or2(&token_list) != NULL)
		return (node);
	return (NULL);
} 

t_treenode *parse_logical_or1(t_token *token_list)
{
	t_treenode *left;
	t_treenode *right;
	t_treenode *node;

	if (left = parse_pipeline_node(token_list) == NULL)
		return (NULL);

	if (token_list->type != LOGICAL_OR)
		return (NULL);
		
	if (right = parse_logical_or_node(token_list) == NULL)
		return (NULL);
	node = create_treenode(token_list->type, token_list->str);
	node->left = left;
	node->right = right;
	return (node);
}

t_treenode *parse_logical_or2(t_token *token_list)
{
	t_treenode *node;
	
	return (node = parse_pipeline_node(token_list));
}
//PARSE_LOGICAL_OR END

//PARSE_PIPELINE
t_treenode *parse_pipeline_node(t_token *token_list)
{
	t_token *tmp = token_list;
	t_treenode *node;

	if (node = parse_pipeline1(&token_list) != NULL)
		return (node);
	if (node = parse_pipeline2(&token_list) != NULL)
		return (node);
	return (NULL);
} 

t_treenode *parse_pipeline1(t_token *token_list)
{
	t_treenode *left;
	t_treenode *right;
	t_treenode *node;

	if (left = parse_command_node(token_list) == NULL)
		return (NULL);

	if (token_list->type != PIPE)
		return (NULL);
		
	if (right = parse_pipeline_node(token_list) == NULL)
		return (NULL);
	node = create_treenode(token_list->type, token_list->str);
	node->left = left;
	node->right = right;
	return (node);
}

t_treenode *parse_pipeline2(t_token *token_list)
{
	t_treenode *node;
	
	return (node = parse_command_node(token_list));
}
//PARSE_PIPELINE END

//PARSE_COMMAND
t_treenode	*parse_command_node(t_token *token_list)
{
	t_treenode *node;

	if (node = parse_command_node1(token_list))
		return (node);
	if (node = parse_command_node2(token_list))
		return (node);

	return (NULL);
}

t_treenode *parse_command_node1(t_token *token_list)
{
	t_treenode *node;
	t_treenode *left;
	t_treenode *right;

	if (token_list->type != BRACKETS_L)
		return (NULL);
	if (right = parse_line_node != NULL)
		return (NULL);
	if (token_list->type != BRACKETS_R)
		return (NULL);
	if (right = parse_command_node1(token_list) != NULL)
		return (NULL);
	node = create_treenode(token_list->type, token_list->str);
	node->left = NULL;
	node->right = right;
	return (node);


}	
t_treenode *parse_command_node2(t_token *token_list) //simple command
{
	t_treenode *node;

	return (node = parse_simple_command_node(token_list));
}

t_treenode	*parse_simple_command_node(t_token *token_list)
{
	t_treenode *node; 

	if (node = parse_simple_command1(token_list))
		return (node);
	if (node = parse_simple_command2(token_list))
		return (node);
	return (NULL);
}
//PARSE_COMMAND END

//PARSE_SIMPLE_COMMAND
t_treenode	*parse_simple_command1(t_token *token_list) 
// par de priorite entre redirection, prio se fait sens de lecture (gauche a droite)
{
	t_treenode *node;
	t_treenode *right;
	t_treenode *left;

	if (left = parse_simple_word_node(token_list) != NULL)
		return (NULL);
	if (parse_redirection_node(token_list) != NULL)
		return (NULL); 

// PAS SUR de devoir laisser celle la 
	if (right = parse_simple_command_node(token_list))
		return (NULL);
}
t_treenode	*parse_simple_command2(t_token *token_list)
{
	t_treenode *node;

	node = parse_simple_word_node(token_list);
	return(node);
}
//PARSE_SIMPLE_COMMAND END

//PARSE_REDIRECTION
t_treenode	*parse_redirection_node(t_token *token_list)
{
	t_treenode *node;

	if (node = parse_redirection1(token_list))
		return (node);
	if (node = parse_redirection2(token_list))
		return (node);
	return (NULL);
}
t_treenode *parse_redirection1(t_token *token_list)
{
	t_treenode *node;
	t_treenode *right;
	t_treenode *left;

	if (token_list->type != INPUT_REDIRECTION || token_list->type != OUTPUT_REDIRECTION 
		|| token_list->type != HERE_DOCUMENT || token_list->type != APPEND_OUTPUT_REDIRECTION)
		return (NULL);
	if (right = parse_simple_word_node(token_list) != NULL)
		return (NULL);
	
	node->left = NULL;
	node->right = right;
}
//PARSE_REDIRECTION END

//PARSE_WORD
t_treenode *parse_word_node(t_token *token_list)
{
	t_treenode *node;

	if (node = parse_word1(token_list))
		return (node);
	return (NULL)
}
t_treenode *parse_word1(t_token *token_list)
{
	t_treenode *node;

	if (token_list == NULL)
		return (NULL);
	if (token_list->type != WORD)
		return (NULL);
	node->left = NULL;
	node->right = NULL;
}
//PARSE_WORD END