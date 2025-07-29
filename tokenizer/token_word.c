/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:49:49 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/29 11:07:14 by lduflot          ###   ########.fr       */
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
char	*token_word(t_token_info *info)
{
	int		inquote;
	char	quote;
	int		i;

	inquote = -1;
	quote = '\0';
	i = *(info->i);
	while (info->line[i] != '\0'
		&& (is_word(info->line[i]) == 1 || info->line[i] == '\n'))
	{
		if ((info->line[i] == '"' || info->line[i] == '\'') && quote == '\0')
			quote = info->line[i];
		if (quote == info->line[i])
			inquote *= -1;
		if ((info->line[i] == '&' && info->line[i + 1] == '&'))
			break ;
		i++;
		if (info->line[i] == ' ' && inquote == -1)
			break ;
	}
	return (check_quote_and_create_token(info, i, inquote, quote));
}

char	*check_quote_and_create_token(t_token_info *info, \
									int i, int inquote, char quote)
{
	if (inquote == 1 && info->line[i] == '\0')
	{
		info->line = read_until_quote_closed(info->line, quote);
		*(info->i) = info->start;
		return (info->line);
	}
	*(info->i) = i;
	return (add_token_word(info->i, info->start, info->line, info->token));
}

char	*add_token_word(int *i, int start, char *line, t_token **token)
{
	char	*str;

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
