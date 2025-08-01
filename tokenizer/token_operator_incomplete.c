/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator_incomplete.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:36:54 by lduflot           #+#    #+#             */
/*   Updated: 2025/08/01 12:09:19 by npederen         ###   ########.fr       */
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
		info->line = loop_newline(info);
		if (!info->line)
		{
			free_token(*(info->token));
			return (NULL);
		}
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
		info->line = loop_newline(info);
		if (!info->line)
		{
			free_token(*(info->token));
			return (NULL);
		}
	}
	else
		token_logical_operator(info);
	return (info->line);
}

char	*loop_newline(t_token_info *info)
{
	char	*next_line;
	char	*tmp;
	char	*tmp_newline;

	while (1)
	{
		next_line = readline_continuation("> ", info->env);
		if (!next_line)
		{
			free(info->line);
			return (NULL);
		}
		tmp = ft_strjoin(info->line, "\n");
		if (!tmp)
			return (free(next_line), free(info->line), NULL);
		tmp_newline = ft_strjoin(tmp, next_line);
		free(tmp);
		free(next_line);
		if (!tmp_newline)
			return (free(info->line), NULL);
		free(info->line);
		info->line = tmp_newline;
		if (ft_isalnum(info->line[ft_strlen(info->line) - 1]))
			break ;
	}
	return (info->line);
}

