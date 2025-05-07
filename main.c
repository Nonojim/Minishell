/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:23:42 by npederen          #+#    #+#             */
/*   Updated: 2025/05/07 15:06:33 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		type;

	quote = line[*i];
	while (line[*i] == quote)
		(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (!line[*i])
	{
		line = read_until_quote_closed(line, quote);
		*i = start - 1;
		//continue ;
		return(1) ;
	}
	str = ft_substr(line, start, *i - start);
	type = type_token(str);
	add_token_end(token, create_token(type, str));
	while (line[*i] == quote)
		(*i)++;
	return (0);
}

//Readline leak ==296785==    still reachable: 214,430 bytes in 259 blocks
int	main(void)
{
	char	*line;
	int		start;
	int		i;
	t_token	*token;
	
	//a delete apres refactor de la partie quote.
	/*int	type;
	char	*str;
	char	quote;*/

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
			{
				//token_quote(&i, start, line, &token);
				if (token_quote(&i, start, line, &token) == 1)
					continue ;
				else
					break;
			}
			////BEGIN A COUPER
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
			/////END
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
