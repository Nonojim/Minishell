/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator_incomplete.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:36:54 by lduflot           #+#    #+#             */
/*   Updated: 2025/08/06 15:51:03 by npederen         ###   ########.fr       */
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
		free(info->line);
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
		free(info->line);
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

static int	line_is_complete_after_operator(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (i >= 0 && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n' \
			|| line[i] == '\v' || line[i] == '\f' || line[i] == '\r'))
		i--;
	if (i < 0 || line[i] == '|' || line[i] == '&' || line[i] == '<' \
		|| line[i] == '>' || line[i] == '(' || line[i] == ')')
		return (0);
	return (1);
}

char	*loop_newline(t_token_info *info)
{
	char	*next_line;
	char	*tmp;

	while (1)
	{
		next_line = readline_continuation("> ", info);
		if (!next_line)
		{
			if (info->line)
				free_then_setnull((void **)&info->line);
			return (info->start = 66, NULL);
		}
		tmp = ft_strjoin(info->line, " ");
		free_then_setnull((void **)&info->line);
		if (!tmp)
			return (free_then_setnull((void **)&next_line), NULL);
		info->line = ft_strjoin(tmp, next_line);
		free_then_setnull((void **)&tmp);
		free_then_setnull((void **)&next_line);
		if (!info->line)
			return (NULL);
		if (line_is_complete_after_operator(info->line))
			break ;
	}
	return (info->line);
}
