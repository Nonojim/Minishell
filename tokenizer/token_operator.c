/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:41:43 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/26 21:01:18 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

//NEW
/*int	is_orlogical_andlogical(char c)
{
	if (c == '|' || c == '&')
		return (1);
	else
		return (0);
}*/
 
/*int	ft_isspace(char *line)
{
	int	i = 0;
	while(line[i])
	{
		if (line[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}*/

char	*token_logical_incomplete(int *i, int start, char *line, t_token **token)
{
	int	type = 0;
	char	*next_line = NULL; //ligne suivante dans readline
	char	*tmp = NULL; //tmp pour concatener
	char	*str = NULL; //token
	char	*tmp_newline= NULL; //tmp pour contacatener 

	// qd line se termine par && ou ||
	// MISS ! si plusieurs espace apres le && en fin de ligne
	if (line[*i + 2] == '\0' /*|| ft_isspace(line)*/)
	{
		while (1)
		{
			next_line = readline(" > ");
			//printf("next_line: [%s]\n", next_line);
			if (!next_line)
				break;
			tmp = ft_strjoin(line, "\n");
			tmp_newline = ft_strjoin(tmp, next_line);
			free (tmp);
			free (next_line);
			free (line);
			if (!tmp_newline)
				break ;
			line = tmp_newline;
			break ;
				//line = tmp;
				//tmp = ft_strjoin(line, next_line);
				//free (line);
				//line = tmp;
				//free (next_line);
			//if (ft_strchr("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890()'", *line))
				//	break;
		}
	}
	// si le premier prompt ne se termine pas par && ou || alors on continue normalement pour créer les tokens.logique
	else
	{
		str = ft_substr(line, start, 2);
		if (!str)
			return (line);
		type = type_token(str);
		add_token_end(token, create_token(type, str));
		*i += 2;
	}
	return (line);
}
//END NEW

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
