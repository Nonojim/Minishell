/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator_incomplete_utils.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:42:51 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/27 18:10:56 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

/*
 * Utils for token_logical_incomplete
 * When the prompt finish by && or || with multiple space
 */
int	only_space_after_op(char *line, int i)
{
	i += 2;
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	only_space_before(char *line, int i)
{
	while (i > 0)
	{
		i--;
		if (line[i] != ' ')
			return (0);
	}
	return (1);
}

int	only_spaces_after_pipe(char *line, int i)
{
	i++;
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	free_unclose_logical(char *tmp, char *next_line, char *line)
{
	if (tmp)
		free(tmp);
	if (next_line)
		free(next_line);
	if (line)
		free(line);
}

int	print_error_logical(char *line, int *j, t_ctx *ctx, int error)
{
	if (error == 1)
		ft_fprintf(2, "minishell: syntax error near unexpected token `%c%c'\n", \
							line[*j], line[*j + 1]);
	else if (error == 2)
		ft_fprintf(2, \
		"minishell: syntax error near unexpected token `newline'\n");
	else if (error == 3)
		ft_fprintf(2, \
		"minishell: syntax error near unexpected token `%c%c'\n", \
		line[*j], line [*j + 1]);
	else if (error == 4)
		ft_fprintf(2, "minishell: syntax error near unexpected token `|'\n");
	else if (error == 5)
		ft_fprintf(2, "minishell: syntax error near unexpected token `%c'\n", \
		line[*j]);
	ctx->exit_code = 2;
	return (1);
}
