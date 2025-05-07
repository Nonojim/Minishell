/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:55:13 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/07 17:40:55 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	while (1)
	{
		next_line = readline("> ");
		if (!next_line)
			break ;
		tmp = line;
		line = ft_strjoin(line, "\n");
		free(tmp);
		tmp = line;
		line = ft_strjoin(line, next_line);
		free(tmp);
		free(next_line);
		if (ft_strchr(line, quote))
			break ;
	}
	return (line);
}

/*
* Identifie and extract token beetween quote
* If the quote is not closed = read_until_closed
* When the same quote is found, prompt is closed and token is create
 */
int	token_quote(int *i, int start, char *line, t_token **token)
{
	char	quote;
	char	*str;

	quote = line[*i];
	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (!line[*i])
	{
		line = read_until_quote_closed(line, quote);
		*i = start - 1;
		return(1) ;
	}
	if (*i - start > 0)
	{
		str = ft_substr(line, start, *i - start);
		add_token_end(token, create_token(WORD, str));
	}
	(*i)++;
	return (0);
}
