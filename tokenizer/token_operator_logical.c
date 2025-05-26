/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator_logical.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:36:54 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/26 23:18:47 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 * When the prompt finish by && or ||
 * MISS : plusieurs espace apres le && ou le ||
 */
char	*token_logical_incomplete(int *i, int start, char *line, t_token **token)
{
	char	*next_line = NULL; //ligne suivante dans readline
	char	*tmp = NULL; //tmp pour concatener
	char	*tmp_newline= NULL; //tmp pour contacatener 

	if (line[*i + 2] == '\0' /*|| ft_isspace(line)*/)
	{
		while (1)
		{
			next_line = readline(" > ");
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
		}
	}
	else
		token_logical_operator(i, start, line, token);
	return (line);
}

/*
* When the bracket in prompt are not closed
* MISS = quand on met dans les new line d'autres type que word = non reconnu en token
* + quand on rajoute des trucs apres la ) les prend en token == non reconnu dans le vrai babash
* + quand on fait (test                  ) = affiche les espace dans l'historique obligé
*/
char	*token_bracket_incomplete(char *line)
{
	char	*next_line;
	char *tmp;

	while (1)
	{
		next_line = readline("> ");
		if (!next_line)
			break ;
		tmp = ft_strjoin(line, ";");
		free(line);
		line = tmp;
		tmp = ft_strjoin(line, next_line);
		free(line);
		line = tmp;
		free(next_line);
		if (ft_strchr(line, ')'))
			break ;
	}
	return (line);
}

char	*token_bracket(int *i, int start, char *line, t_token **token)
{
	char	*str;

	str = ft_substr(line, start, 1);
	add_token_end(token, create_token(BRACKETS_R, str));
	(*i)++;
	if (!ft_strchr(line + *i, ')'))
		line = token_bracket_incomplete(line);
	while (line[*i] && line[*i] != ')')
		(*i)++;
	if (!line[*i])
	{
		line = token_bracket_incomplete(line);
		ft_strchr(line + start, ')');
	}
	else if (line[*i] == ')')
	{
			str = ft_substr(line, start, *i - start);
			add_token_end(token, create_token(WORD, str));
	}
	return (line);
}

