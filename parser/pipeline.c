/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:28:31 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/28 11:37:49 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"


t_treenode *parse_pipeline_node(t_token *token_list);
t_treenode *parse_pipeline1(t_token *token_list);
t_treenode *parse_pipeline2(t_token *token_list);

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
