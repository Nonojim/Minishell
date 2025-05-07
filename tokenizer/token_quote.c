/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:55:13 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/07 14:58:17 by lduflot          ###   ########.fr       */
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
/*char	*read_until_quote_closed(char *line, char quote)
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
}*/
