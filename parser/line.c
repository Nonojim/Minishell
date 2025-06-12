/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:27:07 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/12 21:14:04 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_line_node(t_token **tokens);
t_treenode	*parse_line1(t_token **tokens);
t_treenode	*parse_line2(t_token **tokens);
t_treenode	*parse_line3(t_token **tokens);


void	print_error(t_token **tokens)
{
	if ((*tokens)->type == LOGICAL_OR || (*tokens)->type == LOGICAL_AND || (*tokens)->type == SEMICOLON || (*tokens)->type == PIPE)
		printf("minishell: syntax error near unexpected token '%s'\n", (*tokens)->str);
//	else if ((*tokens)->type == BRACKETS_L || (*tokens)->type == BRACKETS_R )
//		printf("minishell: syntax error near unexpected token '%s'\n", (*tokens)->str);
	//else if ((*tokens)->type == INPUT_REDIRECTION || (*tokens)->type == OUTPUT_REDIRECTION || (*tokens)->type == HERE_DOCUMENT || (*tokens)->type == APPEND_OUTPUT_REDIRECTION)
		//printf("bash: syntax error near unexpected token `newline'\n");
}


t_treenode	*parse_line_node(t_token **tokens)
{
	t_token		*tmp;
	t_treenode	*line_node;

	tmp = *tokens;
	line_node = NULL;
	if ((*tokens) == NULL || tokens == NULL)
		return (NULL);
	line_node = parse_line1(tokens);
	if (line_node != NULL)
		return (line_node);
//	if (*tokens != NULL)
		//print_error(tokens);
	*tokens = tmp;
	line_node = parse_line2(tokens);
	if (line_node != NULL)
		return (line_node);
	//if (*tokens != NULL)
		//print_error(tokens);
	*tokens = tmp;
	line_node = parse_line3(tokens);
	if (line_node != NULL)
		return (line_node);
	/*if (line_node != NULL)
	{
		if (*tokens != NULL)
			print_error(tokens);
		return (line_node);
		*tokens = tmp;
	}*/
	//print_error(tokens);
	return (NULL);
}

//<logical_or> (";" <logical_or>)*
t_treenode	*parse_line1(t_token **tokens)
{
	t_treenode	*left;
	t_treenode	*right;
	t_treenode	*semicolon_node;
	t_token		*semicolon_token;

	left = NULL;
	right = NULL;
	semicolon_node = NULL;
	left = parse_logical_or_node(tokens);
	if (left == NULL && (*tokens)->type == SEMICOLON)
	{
		printf("minishell: syntax error near unexpected token ';'\n");
		return (NULL);	
	}
	if (left == NULL)
		return (NULL);
	if (*tokens == NULL || (*tokens)->type != SEMICOLON)
	{
		free_treenode(left);
		return (NULL);
	}
	semicolon_token = *tokens;
	*tokens = (*tokens)->next;
	if (*tokens == NULL)
	{ 
		free_treenode(left);
		return (NULL);
	}
	right = parse_line_node(tokens);
	if (right == NULL)
	{
		free_treenode(left);
		return(NULL);
	}
	semicolon_node = create_treenode(semicolon_token->type, semicolon_token->str);
	semicolon_node->left = left;
	semicolon_node->right = right;
	return (semicolon_node);
}

//<logical_or> ";"
t_treenode	*parse_line2(t_token **tokens)
{
	t_treenode	*left;
	t_treenode	*semicolon_node;
	t_token		*semicolon_token;

	left = NULL;
	semicolon_node = NULL;
	left = parse_logical_or_node(tokens);
	if (left == NULL)
		return (NULL);
	if (*tokens == NULL || (*tokens)->type != SEMICOLON)
	{
		free_treenode(left);
		return (NULL);
	}
	semicolon_token = *tokens;
	*tokens = (*tokens)->next;
	semicolon_node = create_treenode(semicolon_token->type, semicolon_token->str);
	semicolon_node->left = left;
	semicolon_node->right = NULL;
	return (semicolon_node);
}

//<logical_or>
t_treenode	*parse_line3(t_token **tokens)
{
	t_treenode	*or_node;

	or_node = NULL;
	return (or_node = parse_logical_or_node(tokens));
}
