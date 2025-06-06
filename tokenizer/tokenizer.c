/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:49:49 by npederen          #+#    #+#             */
/*   Updated: 2025/06/06 21:08:03 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*tokenize(t_token *token, char **line_ptr)
{
	char	*line;
	int		start;
	int		i;

	line = *line_ptr;
	i = 0;
	start = 0;
	while (line[i] != '\0')
	{
		while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'
				|| line[i] == '\n'))
			i++;
		start = i;
		line = tokenize2(&i, start, line, &token);
	}
	*line_ptr = line;
	return (token);
}

char	*tokenize2(int	*i, int start, char *line, t_token **token)
{
	if ((line[*i] == '\'' || line[*i] == '\"') && line[*i])
		line = token_quote(i, start, line, token);
	else if ((line[*i] == '&' && line[*i + 1] == '&')
		|| (line[*i] == '|' && line[*i + 1] == '|'))
		line = token_logical_unclose(i, start, line, token);
	else if ((line[*i] == '|'))
		line = token_pipe_unclose(i, start, line, token);
	else if ((line[*i] == '(') && line[*i])
		line = token_bracket(i, start, line, token);
	else if (line[*i] == '$')
		token_expansion(i, start, line, token);
	else if (is_operator_logical(line[*i]) == line[*i] && line[*i])
		token_logical_operator(i, start, line, token);
	else if (line[*i] != '\0' && is_word(line[*i]) == 1)
		token_word(i, start, line, token);
	return (line);
}
