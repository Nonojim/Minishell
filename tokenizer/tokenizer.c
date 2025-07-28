/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:49:49 by npederen          #+#    #+#             */
/*   Updated: 2025/07/28 18:30:28 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_token	*tokenize(t_token *token, char **line_ptr, t_ctx *ctx)
{
	char			*line;
	int				start;
	int				i;
	t_token_info	info;

	line = *line_ptr;
	i = 0;
	start = 0;
	info.i = &i;
	info.start = start;
	info.line = line;
	info.token = &token;
	info.env = ctx;
	while (line && line[i] != '\0' && line[i + 1] != '#')
	{
		while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'
				|| line[i] == '\n'))
			i++;
		start = i;
		info.start = start;
		line = tokenize2(&info);
		if (!line)
			return (NULL);
	}
	*line_ptr = line;
	return (token);
}

char	*tokenize2(t_token_info *info)
{
	int		i;
	char	*line;

	i = *(info->i);
	line = info->line;
	if ((line[i] == '\'' || line[i] == '\"') && line[i])
		line = token_quote(info);
	else if ((line[i] == '&' && line[i + 1] == '&')
		|| (line[i] == '|' && line[i + 1] == '|'))
		line = token_logical_unclose(info);
	else if (line[i] == '|')
		line = token_pipe_unclose(info);
	else if (line[i] == '<' && line[i + 1] == '<')
		line = open_heredoc(info);
	else if (line[i] == '(' && line[i])
		line = token_bracket(info);
	else if (is_operator_logical(line[i]) == line[i] && line[i])
		token_logical_operator(info);
	else if (line[i] != '\0' && is_word(line[i]) == 1)
		line = token_word(info);
	info->line = line;
	return (line);
}
