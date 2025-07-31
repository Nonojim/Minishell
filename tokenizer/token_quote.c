/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:55:13 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/31 18:13:09 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

char	*read_until_quote_closed(t_token_info *info, char quote)
{
	setup_signals_uncomplete_line();
	g_signum = 0;
	info->line = read_quote_loop(info, quote);
	return (info->line);
}

/*
* Continue to read when the user don't close a quote
* When the single || double is found the line is finish
* ft_strjoin(line, "\n");  = emulate the \n that bash produce
* line = ft_strjoin(line, next_line); = join the all new lines to the first one
*/
char	*read_quote_loop(t_token_info *info, char quote)
{
	char	*next_line;

	(void)quote;
	next_line = NULL;
	while (1)
	{
		next_line = readline("> ");
		if (g_signum == 2)
			return (quote_interrupt(info, next_line, 2));
		if (!next_line)
			return (quote_interrupt(info, next_line, 0));
		info->line = create_new_line(info->line, next_line);
		if (is_all_quotes_closed(info->line))
		{
			free(next_line);
			break ;
		}
		else
			free(next_line);
	}
	setup_signals();
	return (info->line);
}

/*
Verifie que toutes les quotes sont fermés
*/
int	is_all_quotes_closed(const char *line)
{
	int		i;
	char	inquote;

	inquote = '\0';
	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			if (inquote == '\0')
				inquote = line[i];
			else if (line[i] == inquote)
				inquote = '\0';
		}
		i++;
	}
	return (inquote == '\0');
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

char	*quote_interrupt(t_token_info *info, char *next_line, int signum)
{
	(void)info;
	if (signum == 2)
	{
		free (next_line);
		//free_token(*(info->token));
		return (NULL);
	}
	if (next_line)
		free(next_line);
	ft_fprintf(2, "minishell: unexpected EOF while looking for \
matching `''\nexit\n");
	return (NULL);
}
