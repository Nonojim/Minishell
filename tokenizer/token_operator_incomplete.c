/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator_incomplete.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:36:54 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/29 11:25:12 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

/*
 * When the prompt finish by && or ||
 */

char	*token_pipe_unclose(t_token_info *info)
{
	if (check_redir_before_logical(info->line, info->i, info->env) == 1
		|| (check_error_after_pipe(info->line, info->i, info->env) == 1))
	{
		free_token(*(info->token));
		return (NULL);
	}
	if (only_spaces_after_pipe(info->line, *(info->i))
		&& !only_space_before(info->line, *(info->i)))
	{
		info->line = loop_newline(info->line);
		if (!info->line)
			return (NULL);
	}
	else
		token_logical_operator(info);
	return (info->line);
}

char	*token_logical_unclose(t_token_info *info)
{
	if (check_redir_before_logical(info->line, info->i, info->env) == 1
		|| check_error_after_logical(info->line, info->i, info->env) == 1)
	{
		free_token(*(info->token));
		return (NULL);
	}
	if (only_space_after_op(info->line, *(info->i))
		&& !only_space_before(info->line, *(info->i)))
	{
		info->line = loop_newline(info->line);
		if (!info->line)
			return (NULL);
	}
	else
		token_logical_operator(info);
	return (info->line);
}

char	*loop_newline(char *line)
{
	char	*next_line;
	char	*tmp;
	char	*tmp_newline;

	while (1)
	{
		next_line = readline("> ");
		if (!next_line)
		{
			free(next_line);
			return (NULL);
		}
		tmp = ft_strjoin(line, "\n");
		tmp_newline = ft_strjoin(tmp, next_line);
		free_unclose_logical(tmp, next_line, NULL);
		if (!tmp_newline)
			return (NULL);
		free(line);
		line = tmp_newline;
		break ;
	}
	return (line);
}
