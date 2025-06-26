/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:41:43 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/26 07:58:19 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

/*
* Check if the character is considered like logical operator
*@return c = it's a logical operator 0 = is not
*/
int	is_operator_logical(char c)
{
	if (c == '|' || c == '&' || c == ';' || c == '<' || c == '>'
		|| c == '(' || c == ')')
	{
		return (c);
	}
	else
		return (0);
}

/*
* Check if the character is considered like double logical operator
* @return 1= is double operator 0=is not
*/
int	is_ok_double(char c)
{
	if (c == '|' || c == '&' || c == '<' || c == '>')
		return (1);
	else
		return (0);
}

void	token_expansion(int *i, int start, char *line, t_token **token)
{
	int		type;
	char	*str;

	if (line[*i] == '$')
	{
		start = *i;
		if (line[*i + 1] && is_word(line[*i + 1]) == 1)
		{
			start = *i;
			while (is_word(line[*i]) && line[*i]
				&& !is_operator_logical(line[*i]))
				(*i)++;
			str = ft_substr(line, start, *i - start);
			type = type_token(str);
			add_token_end(token, create_token(type, str));
		}
		else
		{
			(*i)++;
			str = ft_substr(line, start, 1);
			type = type_token(str);
			add_token_end(token, create_token(type, str));
		}
	}
}

/*
* Identifie and extract logical operator simple or double
* And add to the token list 
 */
void	token_logical_operator(int *i, int start, char *line, t_token **token)
{
	int		type;
	char	*str;

	if (is_operator_logical(line[*i + 1]) == line[*i]
		&& is_ok_double(line[*i]) == 1)
	{
		str = ft_substr(line, start, 2);
		type = type_token(str);
		add_token_end(token, create_token(type, str));
		*i += 2;
	}
	else
	{
		str = ft_substr(line, start, 1);
		type = type_token(str);
		add_token_end(token, create_token(type, str));
		(*i)++;
	}
}
