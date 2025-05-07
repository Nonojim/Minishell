/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:23:42 by npederen          #+#    #+#             */
/*   Updated: 2025/05/07 13:03:28 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Identifie and extract token beetween quote
* If the quote is not closed = read_until_closed
* When the same quote is found, prompt is closed and token is create
 */
void	token_quote(int *i, int start, char *line, t_token **token)
{
	char	quote;
	char	*str;
	int		type;

	quote = line[*i];
	while (line[*i] == quote)
		(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
		i++;
	if (!line[*i])
	{
		line = read_until_quote_closed(line, quote);
		*i = start - 1;
		//continue ;
		//return(1) ;
	}
	str = ft_substr(line, start, *i - start);
	type = type_token(str);
	add_token_end(token, create_token(type, str));
	while (line[*i] == quote)
		(*i)++;
}

//Readline leak ==296785==    still reachable: 214,430 bytes in 259 blocks
int	main(void)
{
	char	*line;
	int		start;
	int		i;
	t_token	*token;

	while (1)
	{
		token = NULL;
		i = 0;
		start = 0;
		//type = -1;
		line = readline("Minishell$ ");
		if (line == NULL)
			break ;
		while (line[i] != '\0')
		{
			//skip whitespaces
			while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'
					|| line[i] == '\n'))
				i++;
			start = i;
			//if single or double quote
			if ((line[i] == '\'' || line[i] == '\"') && line[i])
				token_quote(&i, start, line, &token);
				/*{
				quote = line[i];
				while (line[i] == quote)
					i++;
				start = i;
				while (line[i] && line[i] != quote)
					i++;
				//if its unclosed
				if (!line[i])
				{
					line = read_until_quote_closed(line, quote);
					i = start - 1;
					continue ;
				}
				str = ft_substr(line, start, i - start);
				type = type_token(str);
				add_token_end(&token, create_token(type, str));
				while (line[i] == quote)
					i++;
			}*/
			else if (is_operator_logical(line[i]) == line[i] && line[i])
				token_logical_operator(&i, start, line, &token);
			else if (line[i] != '\0' && is_word(line[i]) == 1)
				token_word(&i, start, line, &token);
		}
		add_history(line);
		print_token_list(token);
		free_token(token);
		free(line);
	}
	return (0);
}
