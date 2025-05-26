/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:49:49 by npederen          #+#    #+#             */
/*   Updated: 2025/05/26 22:32:53 by lduflot          ###   ########.fr       */
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
		if ((line[i] == '\'' || line[i] == '\"') && line[i])
			line = token_quote(&i, start, line, &token);
		//NEW
		else if ((line[i] == '&' && line[i + 1] == '&')
			|| (line[i] == '|' && line[i + 1] == '|'))
			line = token_logical_incomplete(&i, start, line, &token);
		else if((line[i] == '(') && line[i])
			line = token_bracket(&i, start, line, &token);
		// END NEW
		else if (is_operator_logical(line[i]) == line[i] && line[i])
			token_logical_operator(&i, start, line, &token);
		else if (line[i] != '\0' && is_word(line[i]) == 1)
			token_word(&i, start, line, &token);
	}
	*line_ptr = line;
	return (token);
}
