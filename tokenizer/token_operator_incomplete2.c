/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator_incomplete2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:22:54 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/31 17:30:08 by npederen         ###   ########.fr       */
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
