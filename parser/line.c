/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:27:07 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/05 12:43:19 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_line_node(t_token **token_list);
t_treenode	*parse_line1(t_token **token_list);
t_treenode	*parse_line2(t_token **token_list);
t_treenode	*parse_line3(t_token **token_list);

void	print_error(t_token **token_list)
{
	if ((*token_list) == NULL)
		return ;
	if ((*token_list)->type == LOGICAL_OR || (*token_list)->type == LOGICAL_AND || (*token_list)->type == SEMICOLON || (*token_list)->type == PIPE)
		printf("bash: syntax error near unexpected token `%s'\n", (*token_list)->str);
	if ((*token_list)->type == INPUT_REDIRECTION)
		printf("bash: test: No such file or directory\n");
}

t_treenode	*parse_line_node(t_token **token_list)
{
	t_token		*tmp;
	t_treenode	*node;

	tmp = *token_list;
	node = NULL;
	node = parse_line1(token_list);
	if (node != NULL)
		return (node);
	*token_list = tmp;
	free_treenode(node);
	node = parse_line2(token_list);
	if (node != NULL)
		return (node);
	*token_list = tmp;
	free_treenode(node);
	node = parse_line3(token_list);
	if (node != NULL)
		return (node);
	*token_list = tmp;
	free_treenode(node);
	print_error(token_list);
	return (NULL);
}

//<logical_or> (";" <logical_or>)*
t_treenode	*parse_line1(t_token **token_list)
{
	t_treenode	*left;
	t_treenode	*right;
	t_treenode	*node;
	t_token		*create_node;

	left = NULL;
	right = NULL;
	node = NULL;
	left = parse_logical_or_node(token_list);
	if (left == NULL)
		return (NULL);
	if (*token_list == NULL || (*token_list)->type != SEMICOLON)
	{
		//free_treenode(left);
		return (NULL);
	}
	create_node = *token_list;
	*token_list = (*token_list)->next;
	if (*token_list == NULL)
	{ 
		free_treenode(left);
		right = NULL;
	}
	right = parse_line_node(token_list);
	if (right == NULL)
	{
			//free_treenode(left);
			return(NULL);
	}
	node = create_treenode(create_node->type, create_node->str);
	node->left = left;
	node->right = right;
	return (node);
}

//<logical_or> ";"
t_treenode	*parse_line2(t_token **token_list)
{
	t_treenode	*left;
	t_treenode	*node;
	t_token		*create_node;

	left = NULL;
	node = NULL;
	left = parse_logical_or_node(token_list);
	if (left == NULL)
		return (NULL);
	if (*token_list == NULL || (*token_list)->type != SEMICOLON)
	{
		free_treenode(left);
		return (NULL);
	}
	create_node = *token_list;
	*token_list = (*token_list)->next;
	node = create_treenode(create_node->type, create_node->str);
	node->left = left;
	node->right = NULL;
	return (node);
}

//<logical_or>
t_treenode	*parse_line3(t_token **token_list)
{
	t_treenode	*node;

	node = NULL;
	return (node = parse_logical_or_node(token_list));
}
