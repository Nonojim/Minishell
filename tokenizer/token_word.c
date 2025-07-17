/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:49:49 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/17 14:24:29 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

/*
* Check if the character is valid a part of a token word
* Eliminate special characters
* @return 1 = it's a valid word character 0 = is not
*/
 int    is_word(int c)
{
    unsigned char uc = (unsigned char)c;

    if (uc >= 128) // UTF-8 multibyte chars (à partir de 0x80)
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
	int		inquote = -1;
	char	quote;
	//int		diff = 0;

	quote = '\0';
	while (line[*i] != '\0' && (is_word(line[*i]) == 1 || line[*i] == '\n'))
	{
		if((line[*i] == '"' || line[*i] == '\'' ) && quote == '\0')
			quote = line[*i];
		if (quote == line[*i])
			inquote *= -1;
		if ((line[*i] == '&' && line[*i + 1] == '&'))
			break;
		(*i)++;
		if(line[*i] == ' ' && inquote == -1)
			break;
	}
	if (inquote == 1 && line[*i] == '\0')
	{
		//setup_signal_heredoc();
		line = read_until_quote_closed(line, quote);
		//setup_signals();
		*i = start;
		return (line);
		//str = ft_strdup(line);
		//str = read_until_quote_closed(str, quote);
		//diff = ft_strlen(str) - *i;
		//if (diff < 0)
		//	diff *= -1;
		//*i += diff;
	}	
	else
		str = ft_substr(line, start, *i - start);
	if (!str)
		return (NULL);
		//printf("ICI [%s]\n", str);
	if (is_word(*str) == 1)
	{
		add_token_end(token, create_token(WORD, str));
		// free(str);
	}
	else
	{
		(*i)++;
		free (str);
	}
	return (line);
}

