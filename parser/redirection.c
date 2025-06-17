/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:28:49 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/17 12:29:22 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_redirection_node(t_token **tokens);
t_treenode	*parse_redirection1(t_token **tokens);
t_treenode	*settoken_thenreturn(t_token **tokenstoset, t_token *setting);

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
	if (*tokens == NULL)
		return (printerror_then_return_null(tokens));
	if (!is_word_type((*tokens)->type))
		return (printerror_then_return_null(&redir_token));
	right = parse_word_node(tokens);
	if (right == NULL)
		return (settoken_thenreturn(tokens, redir_token));
	redir_node = create_treenode(redir_token->type, redir_token->str);
	redir_token = *tokens;
	if (redir_node == NULL)
		return (free_then_return_null(right));
	redir_node->right = right;
	return (redir_node);
}

t_treenode	*settoken_thenreturn(t_token **tokenstoset, t_token *setting)
{
	*tokenstoset = setting;
	return (NULL);
}
