/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator_incomplete.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:36:54 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/27 14:19:53 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"


int	type_token_redir(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '>' && str[1] == '>')
		return (APPEND_OUTPUT_REDIRECTION);
	else if (str[0] == '>')
		return (OUTPUT_REDIRECTION);
	else if (str[0] == '<')
		return (INPUT_REDIRECTION);
	return (0);

}
int	type_token_operator(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '&' && str[1] == '&')
		return (LOGICAL_AND);
	else if (str[0] == '|' && str[1] == '|')
		return (LOGICAL_OR);
	else if (str[0] == '|')
		return (PIPE);
	return(0);
}
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
			ft_fprintf(2, "minishell: syntax error near unexpected token `%c'\n", \
							line[*i]);
		else
			ft_fprintf(2, "minishell: syntax error near unexpected token `%c%c'\n", \
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
	{
		ft_fprintf(2, "minishell: syntax error near unexpected token `%c%c'\n", \
							line[j], line[j + 1]);
		ctx->exit_code = 2;
		return (1);
	}
	if (type_token_redir(&line[j]))
	{
		j++;
		while (line[j] == ' ')
			j++;
		if (line[j] == '\0' && ((line[0] != '&' || line[1] != '&' ) && (line[0] != '|' || line[1] != '|')))
		{
				ft_fprintf(2, "minishell: syntax error near unexpected token `newline'\n");
				ctx->exit_code = 2;
				return (1);
		}
		if(line[j] == '\0' || type_token_operator(&line[j]))
		{
				ft_fprintf(2, "minishell: syntax error near unexpected token `%c%c'\n", line[*i], line [*i + 1]);
				ctx->exit_code = 2;
				return (1);
		}
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
			free (tmp);
			free (next_line);
			free (line);
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

int	check_error_after_pipe(char *line, int *i, t_ctx *ctx)
{
	int	j;

	j = 0;
	j = *i + 1 ;
	while (line[j] == ' ')
		j++;
	if (type_token_operator(&line[j]))
	{
		ft_fprintf(2, "minishell: syntax error near unexpected token `|'\n");
		ctx->exit_code = 2;
		return (1);
	}
	if (type_token_redir(&line[j]))
	{
		j++;
		while (line[j] == ' ')
			j++;
		if (line[j] == '\0' && line[0] != '|')
		{
				ft_fprintf(2, "minishell: syntax error near unexpected token `newline'\n");
				ctx->exit_code = 2;
				return (1);
		}
		if(line[j] == '\0' || type_token_operator(&line[j]))
		{
				ft_fprintf(2, "minishell: syntax error near unexpected token `%c'\n", line[*i]);
				ctx->exit_code = 2;
				return (1);
		}
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
			free (tmp);
			free (next_line);
			free (line);
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
