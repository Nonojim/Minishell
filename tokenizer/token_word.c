/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:49:49 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/28 07:37:06 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

/*
* Check if the character is valid a part of a token word
* Eliminate special characters
* Take UTF_8
* @return 1 = it's a valid word character 0 = is not
*/
int	is_word(int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	if (uc >= 128)
		return (1);
	if (uc == '|' || uc == '<' || uc == '>' || uc == ';'
		|| uc == '(' || uc == ')')
		return (0);
	if ((uc >= 32 && uc <= 126) || uc == '\\' || uc == '"' || uc == '\'')
		return (1);
	return (0);
}

/*
* Extract the token word and add to the token_list
* Word is defined as sequence of the characters who are not a special token
 */
char	*token_word(int *i, int start, char *line, t_token **token)
{
	char	*str;
	int		inquote;
	char	quote;

	inquote = -1;
	quote = '\0';
	while (line[*i] != '\0' && (is_word(line[*i]) == 1 || line[*i] == '\n'))
	{
		if ((line[*i] == '"' || line[*i] == '\'' ) && quote == '\0')
			quote = line[*i];
		if (quote == line[*i])
			inquote *= -1;
		if ((line[*i] == '&' && line[*i + 1] == '&'))
			break ;
		(*i)++;
		if (line[*i] == ' ' && inquote == -1)
			break ;
	}
	if (inquote == 1 && line[*i] == '\0')
	{
		line = read_until_quote_closed(line, quote);
		*i = start;
		return (line);
	}
	else
		str = ft_substr(line, start, *i - start);
	if (!str)
		return (NULL);
	if (is_word(*str) == 1)
		add_token_end(token, create_token(WORD, str));
	else
	{
		(*i)++;
		free (str);
	}
	return (line);
}
