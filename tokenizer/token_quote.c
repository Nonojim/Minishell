/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:55:13 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/28 18:20:18 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

char	*read_until_quote_closed(char *line, char quote)
{
	setup_signals_uncomplete_line();
	g_signum = 0;
	line = read_quote_loop(line, quote);
	return (line);
}

/*
* Continue to read when the user don't close a quote
* When the single || double is found the line is finish
* ft_strjoin(line, "\n");  = emulate the \n that bash produce
* line = ft_strjoin(line, next_line); = join the all new lines to the first one
* if (ft_strchr(line, quote)) = check if quote is closed
*/
char	*read_quote_loop(char *line, char quote)
{
	char	*next_line;

	next_line = NULL;
	while (1)
	{
		next_line = readline("> ");
		if (g_signum == 2)
			return (quote_interrupt(next_line, 2));
		if (!next_line)
			return (quote_interrupt(next_line, 0));
		line = create_new_line(line, next_line);
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

char	*create_new_line(char *line, char *next_line)
{
	char	*tmp;

	tmp = ft_strjoin(line, "\n");
	free(line);
	line = tmp;
	tmp = ft_strjoin(line, next_line);
	free(line);
	line = tmp;
	return (line);
}

char	*quote_interrupt(char *next_line, int signum)
{
	if (signum == 2)
	{
		free (next_line);
		return (NULL);
	}
	if (next_line)
		free(next_line);
	ft_fprintf(2, "minishell: unexpected EOF while looking for \
							matching `\"'\nexit\n");
	return (NULL);
}

/*
* Identifie and extract token beetween quote
* If the quote is not closed = read_until_closed
* When the same quote is found, prompt is closed and token is create
 */
char	*token_quote(t_token_info *info)
{
	char	quote;
	char	*str;
	int		i;

	i = *(info->i);
	quote = info->line[i];
	info->start = i;
	i++;
	while (info->line[i] && info->line[i] != quote)
		i++;
	if (!info->line[i])
	{
		info->line = read_until_quote_closed(info->line, quote);
		*(info->i) = info->start;
		return (info->line);
	}
	while (info->line[i] && is_word(info->line[i]) && info->line[i] != ' ')
		i++;
	str = ft_substr(info->line, info->start, i - info->start);
	add_token_end(info->token, create_token(WORD, str));
	*(info->i) = i;
	setup_signals();
	return (info->line);
}
