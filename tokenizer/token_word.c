/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:49:49 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/07 12:50:25 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
* Check if the character is valid a part of a token word
* Eliminate special characters
* @return 1 = it's a valid word character 0 = is not
*/
int	is_word(int c)
{
	if (c == '&' || c == '|' || c == '<' || c == '>' || c == ';'
		|| c == '(' || c == ')' || c == '"' || c == '\'')
		return (0);
	if ((c >= 33 && c <= 126) || c == '\\')
		return (1);
	return (0);
}

/*
* Extract the token word and add to the token_list
* Word is defined as sequence of the characters who are not a special token
 */
void	token_word(int *i, int start, char *line, t_token **token)
{
	char	*str;

	while (line[*i] != '\0' && is_word(line[*i]) == 1)
		(*i)++;
	str = ft_substr(line, start, *i - start);
	if (is_word(*str) == 1)
		add_token_end(token, create_token(WORD, str));
	else
		(*i)++;
}
