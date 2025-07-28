/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:41:43 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/28 18:26:23 by lduflot          ###   ########.fr       */
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

/*
* Identifie and extract logical operator simple or double
* And add to the token list 
 */
void	token_logical_operator(t_token_info *info)
{
	int		type;
	char	*str;
	int		i;

	i = *(info->i);
	if (is_operator_logical(info->line[i + 1]) == info->line[i]
		&& is_ok_double(info->line[i]) == 1)
	{
		str = ft_substr(info->line, info->start, 2);
		type = type_token(str);
		add_token_end(info->token, create_token(type, str));
		i += 2;
	}
	else
	{
		str = ft_substr(info->line, info->start, 1);
		type = type_token(str);
		add_token_end(info->token, create_token(type, str));
		i++;
	}
	*(info->i) = i;
}
