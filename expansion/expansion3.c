/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 17:43:35 by lduflot           #+#    #+#             */
/*   Updated: 2025/08/09 20:16:55 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

//*i>0 (et pour l'invalid read of size lié au str[*i-1]
//Ces deux fonction gères : "$" ou '$' et $4HOME = HOME ou $'HOME' = HOME
int	var_with_number_after_dollar(int *j, char *str, int *i)
{
	if (*i > 0 && str[*i] && (str[*i - 1] == '\'' || str[*i - 1] == '"') && (str[*i] == '$')
		&& (str[*i + 1] == '\'' || str[*i + 1] == '"'))
		return (0);
	if (str[*i] == '$'
		&& ft_isdigit(str[*i + 1]))
	{
		*j = *i + 1;
		while (ft_isdigit(str[*j]))
			(*j)++;
		*i = *j;
		return (1);
	}
	return (0);
}

int	var_with_quote_after_dollar(int *j, char **result, char *str, int *i)
{
	if (*i > 0 && str[*i] && (str[*i - 1] == '\'' || str[*i - 1] == '"') && (str[*i] == '$')
		&& (str[*i + 1] == '\'' || str[*i + 1] == '"'))
		return (0);
	if (str[*i] == '$'
		&& (str[*i + 1] == '\'' || str[*i + 1] == '"'))
	{
		*j = *i + 2;
		while (str[*j] && (str[*j] != '\'' || str[*j] != '"'))
		{
			add_char_to_string(result, str[*j]);
			(*j)++;
		}
		if (str[*j] == '\'')
			(*j)++;
		*i = *j;
		return (1);
	}
	return (0);
}
