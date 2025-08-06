/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:55:13 by lduflot           #+#    #+#             */
/*   Updated: 2025/08/06 17:51:49 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

char	*read_until_quote_closed(t_token_info *info, char quote)
{
	info->line = read_quote_loop(info, quote);
	if (!info->line)
		free_token(*(info->token));
	return (info->line);
}

char	*read_quote_loop(t_token_info *info, char quote)
{
	char	*next_line;
	char	*tmp;

	quote = '1';
	next_line = NULL;
	while (1)
	{
		next_line = readline_continuation("> ", info);
		if (!next_line)
			return (missing_next_line(info));
		tmp = join_state_quote(info, &quote);
		free_then_setnull((void **)&info->line);
		if (!tmp)
			return (free_then_setnull((void **)&next_line), NULL);
		info->line = ft_strjoin(tmp, next_line);
		free_then_setnull((void **)&tmp);
		free_then_setnull((void **)&next_line);
		if (!info->line)
			return (NULL);
		if (is_all_quotes_closed(info->line))
			break ;
	}
	return (info->line);
}

char	*join_state_quote(t_token_info *info, char *quote)
{
	char	*tmp;

	if (*quote == '1')
		tmp = ft_strjoin(info->line, "\n");
	else
		tmp = ft_strjoin(info->line, "");
	*quote = '0';
	return (tmp);
}

char	*missing_next_line(t_token_info *info)
{
	info->start = 66;
	if (info->line)
		free_then_setnull((void **)&info->line);
	return (NULL);
}

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
