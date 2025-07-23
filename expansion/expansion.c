/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:05:41 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/23 12:21:16 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void	expanse_ast(t_treenode *node, t_ctx *ctx)
{
	if (!node)
		return ;
	if (node->type == HERE_DOCUMENT)
	{
		expanse_heredoc(node, ctx);
		return ;
	}
	if (node->type == INPUT_REDIRECTION
		|| node->type == OUTPUT_REDIRECTION
		|| node->type == APPEND_OUTPUT_REDIRECTION)
		expanse_redir(node, ctx);
	if (node->argv)
		expanse_argv(node, ctx);
}

void	expanse_heredoc(t_treenode *node, t_ctx *ctx)
{
	char	*expanded;

	if (node->str && (node->str[0] == '\'' || node->str[0] == '"'))
		return ;
	if (node->right && node->right->str)
	{
		expanded = expand_heredoc(node->right->str, ctx);
		free(node->right->str);
		node->right->str = expanded;
	}
}

void	expanse_redir(t_treenode *node, t_ctx *ctx)
{
	char	*expanded;
	char	*clean;

	if (node->right && node->right->str)
	{
		expanded = expand_string(node->right->str, node, ctx);
		if (expanded == NULL)
		{
			clean = remove_quotes_after_expansion(node->right->str);
			free(node->right->str);
			node->right->str = clean;
		}
		if (expanded != NULL && (ft_strchr(expanded, '\'')
				|| ft_strchr(expanded, '"')))
		{
			clean = remove_quotes_after_expansion(expanded);
			free(node->right->str);
			free(expanded);
			node->right->str = clean;
		}
		else
		{
			free(node->right->str);
			node->right->str = expanded;
		}
	}
}

void	expanse_argv(t_treenode *node, t_ctx *ctx)
{
	char	*clean;
	char	*expanded;
	int		i;

	i = 0;
	while (node->argv[i])
	{
		expanded = expand_string(node->argv[i], node, ctx);
		if (!expanded)
			clean = remove_quotes_after_expansion(node->argv[i]);
		else if (ft_strchr(expanded, '\'')
			|| ft_strchr(expanded, '"'))
		{
			clean = remove_quotes_after_expansion(expanded);
			free(expanded);
		}
		else
			clean = expanded;
		free(node->argv[i]);
		node->argv[i] = clean;
		i++;
	}
}
