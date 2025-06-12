/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:27:49 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/12 21:11:54 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_logical_and_node(t_token **tokens);
t_treenode	*parse_logical_and1(t_token **tokens);
t_treenode	*parse_logical_and2(t_token **tokens);

t_treenode	*parse_logical_and_node(t_token **tokens)
{
	t_token		*tmp;
	t_treenode	*and_node;

	tmp = *tokens;
	and_node = NULL;
	and_node = parse_logical_and1(tokens);
	if (and_node != NULL)
		return (and_node);
	*tokens = tmp;
	and_node = parse_logical_and2(tokens);
	if (and_node != NULL)
		return (and_node);
	*tokens = tmp;
	return (NULL);
}

//create_node = avant d'avancer dans la liste afin de créer le bon node (et pas le noeud suivant).
//<pipeline> ("||"  <pipeline> )* 
t_treenode	*parse_logical_and1(t_token **tokens)
{
	t_treenode	*left;
	t_treenode	*right;
	t_treenode	*and_node;
	t_token		*and_token;

	left = NULL;
	right = NULL;
	and_node = NULL;
	if (*tokens == NULL || 
   ((*tokens)->type != WORD && (*tokens)->type != BRACKETS_L))
	{
		printf("minishell: syntax error near unexpected token '%s'\n", (*tokens)->str);
		return (NULL);
	}
	left = parse_pipeline_node(tokens);
	if (left == NULL)
		return (NULL);
	if (*tokens == NULL || (*tokens)->type != LOGICAL_AND)
	{
		free_treenode(left);
		return (NULL);
	}
	and_token = *tokens;
	*tokens = (*tokens)->next;
	right = parse_logical_and_node(tokens);
	if (right == NULL)
	{
		free_treenode(left);
		return (NULL);
	}
	and_node = create_treenode(and_token->type, and_token->str);
	and_node->left = left;
	if (right->type == and_token->type) // si a droite se trouve un autre &&
	{
		and_node->right = right->left;
		right->left = and_node;
		return (right);
	}
	else
	{
		and_node->right = right;
		return (and_node);
	}
}

//	<pipeline>
t_treenode	*parse_logical_and2(t_token **tokens)
{
	t_treenode	*pipe_node;
	
	pipe_node = NULL;
	return (pipe_node = parse_pipeline_node(tokens));
}
