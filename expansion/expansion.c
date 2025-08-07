/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:05:41 by lduflot           #+#    #+#             */
/*   Updated: 2025/08/07 20:05:36 by lduflot          ###   ########.fr       */
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
	expanse_ast(node->left, ctx);
	expanse_ast(node->right, ctx);
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

	if (!node || !node->right || !node->right->str)
		return ;
	expanded = expand_string(node->right->str, node, ctx, 0);
	if (!expanded)
		return ;
	if (expanded != NULL && (ft_strchr(expanded, '\'')
			|| ft_strchr(expanded, '"')))
	{
		if (ft_strchr(expanded, '*'))
			return ;
		clean = remove_quotes_after_expansion(expanded);
		free_redir(node, expanded);
		node->right->str = clean;
	}
	else
	{
		free_redir(node, NULL);
		node->right->str = expanded;
	}
}

void	free_redir(t_treenode *node, char *expanded)
{
	if (node)
		free(node->right->str);
	if (expanded)
		free(expanded);
}

void	expanse_argv(t_treenode *node, t_ctx *ctx)
{
	char	*clean;
	char	*expanded;
	int		i;

	i = 0;
	while (node->argv[i])
	{
		expanded = expand_string(node->argv[i], node, ctx, i);
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
	delete_var_empty(node);
}
