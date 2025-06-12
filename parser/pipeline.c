/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:28:31 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/12 21:12:18 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_pipeline_node(t_token **tokens);
t_treenode	*parse_pipeline1(t_token **tokens);
t_treenode	*parse_pipeline2(t_token **tokens);

t_treenode	*parse_pipeline_node(t_token **tokens)
{
	t_token		*tmp;
	t_treenode	*pipe_node;

	tmp = *tokens;
	pipe_node = NULL;
	pipe_node = parse_pipeline1(tokens);
	if (pipe_node != NULL)
		return (pipe_node);
	*tokens = tmp;
	pipe_node = parse_pipeline2(tokens);
	if (pipe_node != NULL)
		return (pipe_node);
	*tokens = tmp;
	return (NULL);
}

//<command> "|" <command>
t_treenode	*parse_pipeline1(t_token **tokens)
{
	t_treenode	*left;
	t_treenode	*right;
	t_treenode	*pipe_node;
	t_token		*pipe_token;

	if (*tokens == NULL || 
	   ((*tokens)->type != WORD && (*tokens)->type != BRACKETS_L))
	{
		printf("minishell: syntax error near unexpected token '%s'\n", (*tokens)->str);
		return (NULL);
	}
	left = parse_command_node(tokens);
	if (left == NULL)
		return (NULL);
	//Si pas de pipe on return le node left pour éviter de reparser left 
	if (*tokens == NULL || (*tokens)->type != PIPE)
		return (left);
	pipe_token = *tokens;
	*tokens = (*tokens)->next;
	//appel récursif qui remplace le while pour gérer si il y a plusieurs pipe
	if (*tokens == NULL || !is_word_type((*tokens)->type))
	{
		if (is_redirection((*tokens)->type))
			printf("minishelm: syntax error near unexpected token `newline'\n");
		else
			printf("minishell: syntax error near unexpected token `%s'\n", (*tokens)->str);
		free_treenode(left);
		return(NULL);
	}
	right = parse_pipeline1(tokens);
	if (right == NULL)
	{
		free_treenode(left);
		return (NULL);
	}
	pipe_node = create_treenode(pipe_token->type, pipe_token->str);
	pipe_node->left = left;
	pipe_node->right = right;
	return (pipe_node);
}

//<command>
t_treenode	*parse_pipeline2(t_token **tokens)
{
	t_treenode	*command_node;

	command_node = NULL;
	return (command_node = parse_command_node(tokens));
}
