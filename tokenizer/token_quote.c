/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:55:13 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/27 10:40:10 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

/*
* Continue to read when the user don't close a quote
* When the single || double is found the line is finish
* ft_strjoin(line, "\n");  = emulate the \n that bash produce
* line = ft_strjoin(line, next_line); = join the all new lines to the first one
* if (ft_strchr(line, quote)) = check if quote is closed
*/
char	*read_until_quote_closed(char *line, char quote)
{
	char	*next_line;
	char	*tmp;

	next_line = NULL;
	setup_signals_uncomplete_line();
	g_signum = 0;
	while (1)
	{
		next_line = readline("> ");
		if (g_signum == 2)
		{
			free(next_line);
			return (NULL);
		}
		if (!next_line)
		{
			free(next_line);
			printf("bash: unexpected EOF while looking for \
							matching `\"'\nexit\n");
			return (NULL);
		}
		tmp = ft_strjoin(line, "\n");
		free(line);
		line = tmp;
		tmp = ft_strjoin(line, next_line);
		free(line);
		line = tmp;
		if (ft_strchr(next_line, quote))
		{
			free(next_line);
			break ;
		}
		else
			free(next_line);
	}
	setup_signals();
	return (line);
}

/*
* Identifie and extract token beetween quote
* If the quote is not closed = read_until_closed
* When the same quote is found, prompt is closed and token is create
 */
char	*token_quote(int *i, int start, char *line, t_token **token)
{
	char	quote;
	char	*str;

	quote = line[*i];
	start = *i;
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (!line[*i])
	{
		line = read_until_quote_closed(line, quote);
		*i = start;
		return (line);
	}
	while (line[*i] && is_word(line[*i]) && line[*i] != ' ')
		(*i)++;
	str = ft_substr(line, start, *i - start);
	add_token_end(token, create_token(WORD, str));
	setup_signals();
	return (line);
}
