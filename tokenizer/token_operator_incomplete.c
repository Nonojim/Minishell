/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator_incomplete.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:36:54 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/27 18:08:48 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	check_redir_before_logical(char *line, int *i, t_ctx *ctx)
{
	int	j;

	j = 0;
	j = *i - 1;
	while (j >= 0 && line[j] == ' ')
		j--;
	if (j >= 0 && (line[j] == '<' || line[j] == '>'))
	{
		if (line[*i] == '|' && line[*i + 1] != '|')
			ft_fprintf(2, \
			"minishell: syntax error near unexpected token `%c'\n", \
			line[*i]);
		else
			ft_fprintf(2, \
			"minishell: syntax error near unexpected token `%c%c'\n", \
			line[*i], line[*i + 1]);
		ctx->exit_code = 2;
		return (1);
	}
	return (0);
}

int	check_error_after_logical(char *line, int *i, t_ctx *ctx)
{
	int	j;

	j = 0;
	j = *i + 2 ;
	while (line[j] == ' ')
		j++;
	if (type_token_operator(&line[j]))
		return (print_error_logical(line, &j, ctx, 1));
	if (type_token_redir(&line[j]))
	{
		j++;
		while (line[j] == ' ')
			j++;
		if (line[j] == '\0' && ((line[0] != '&' || line[1] != '&' )
				&& (line[0] != '|' || line[1] != '|')))
			return (print_error_logical(line, &j, ctx, 2));
		if (line[j] == '\0' || type_token_operator(&line[j]))
			return (print_error_logical(line, i, ctx, 3));
	}
	return (0);
}

/*
 * When the prompt finish by && or ||
 */
char	*token_logical_unclose(int *i, int start, \
										char *line, t_token **token, t_ctx *ctx)
{
	char	*next_line;
	char	*tmp;
	char	*tmp_newline;

	if (check_redir_before_logical(line, i, ctx) == 1)
		return (NULL);
	if (check_error_after_logical(line, i, ctx) == 1)
		return (NULL);
	if (only_space_after_op(line, *i) && !only_space_before(line, *i))
	{
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
			free_unclose_logical(tmp, next_line, line);
			if (!tmp_newline)
				break ;
			line = tmp_newline;
			break ;
		}
	}
	else
		token_logical_operator(i, start, line, token);
	return (line);
}

int	check_error_after_pipe(char *line, int *i, t_ctx *ctx)
{
	int	j;

	j = 0;
	j = *i + 1 ;
	while (line[j] == ' ')
		j++;
	if (type_token_operator(&line[j]))
		return (print_error_logical(line, &j, ctx, 4));
	if (type_token_redir(&line[j]))
	{
		j++;
		while (line[j] == ' ')
			j++;
		if (line[j] == '\0' && line[0] != '|')
			return (print_error_logical(line, &j, ctx, 2));
		if (line[j] == '\0' || type_token_operator(&line[j]))
			return (print_error_logical(line, i, ctx, 5));
	}
	return (0);
}

char	*token_pipe_unclose(int *i, int start, char *line, \
													t_token **token, t_ctx *ctx)
{
	char	*next_line;
	char	*tmp;
	char	*tmp_newline;

	if (check_redir_before_logical(line, i, ctx) == 1)
		return (NULL);
	if (check_error_after_pipe(line, i, ctx) == 1)
		return (NULL);
	if (only_spaces_after_pipe(line, *i) && !only_space_before(line, *i))
	{
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
			free_unclose_logical(tmp, next_line, line);
			if (!tmp_newline)
				break ;
			line = tmp_newline;
			break ;
		}
	}
	else
		token_logical_operator(i, start, line, token);
	return (line);
}
