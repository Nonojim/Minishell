/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:28:49 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/13 17:55:28 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_redirection_node(t_token **tokens);
t_treenode	*parse_redirection1(t_token **tokens);

/*
<redirection>				::= ( "<" | "<<" | ">" | ">>" ) <word>
*/
t_treenode	*parse_redirection_node(t_token **tokens)
{
	t_treenode	*redir_node;
	t_token		*tmp;

	redir_node = NULL;
	tmp = *tokens;
	if (parse_error(-1) == 1)
		return (NULL);
	redir_node = parse_redirection1(tokens);
	if (parse_error(-1) == 1)
		return (NULL);
	if (redir_node != NULL)
		return (redir_node);
	*tokens = tmp;
	return (NULL);
}

t_treenode	*parse_redirection1(t_token **tokens)
{
	t_treenode	*redir_node;
	t_treenode	*right;
	t_token		*redir_token;

	redir_node = NULL;
	right = NULL;
	if (*tokens == NULL)
		return (NULL);
	if (!is_redirection((*tokens)->type))
		return (NULL);
	redir_token = *tokens;
	*tokens = (*tokens)->next;
	if (*tokens == NULL || !is_word_type((*tokens)->type))
	{
		//if (*tokens == NULL)
			//print_error(*tokens);
	//	else
		//	print_error(*tokens);
			//printf("minishell: syntax error near unexpected token `newline'\n"); // l'affiche trop de fois
		//else //str est autre chose qu'un word
			//printf("minishell: syntax error near unexpected token '%s'\n", (*tokens)->str); // l'affiche trop de fois
		//print_error(tokens);
		//if (*tokens)
			//*tokens = (*tokens)->next;
		//*tokens = redir_token;
			return (NULL);
	}
	right = parse_word_node(tokens);
	if (right == NULL)
	{
		*tokens = redir_token;
		return (NULL);
	}
	redir_node = create_treenode(redir_token->type, redir_token->str);
	redir_token = *tokens;
	if (redir_node == NULL)
	{
		free_treenode(right);
		return (NULL);
	}
	redir_node->right = right;
	return (redir_node);
}
