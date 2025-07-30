/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:49:49 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/30 22:40:35 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

/*
* Extract the token word and add to the token_list
* Word is defined as sequence of the characters who are not a special token
* Fonction parcourt caractère par caractère
* Gestion des quotes:
* inquote = 0 si on est hors quote inquote = 1 si on est inside
* quote = stock le type de quote (' ou ")
* lorsqu'on rencontre la même quote on ferme inquote = 0
* tant quond est dans une quote tous les caractere sont acceptés 
* En dehors de quote le mot stop sur space, op logique, redir
* Si quote non fermé elle sera demandé avec une newline
 */
char	*token_word(t_token_info *info)
{
	int		i;
	int		inquote;
	char	quote;

	i = *(info->i);
	inquote = 0;
	quote = '\0';
	while (info->line[i])
	{
		//avant interieur mis dans if_in_quote mais ne veut pas marcher, normin a revoir.
		if ((info->line[i] == '"' || info->line[i] == '\''))
		{
			if (!inquote)
			{
				inquote = 1;
				quote = info->line[i];
			}
			else if (info->line[i] == quote)
			{
				inquote = 0;
				quote = '\0';
			}
			i++;
			continue;
		}
		if (!inquote)
		{
			if (info->line[i] == ' '
				|| (info->line[i] == '&' && info->line[i + 1] == '&')
				|| !is_word(info->line[i]))
				break ;
		}
		i++;
	}
	*(info->i) = i;
	return (check_quote_and_create_token(info, i, inquote, &quote));
}

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
Met à jour l'état de la quote 
Ignore les quote differentes jusqu'à que la premiere quote soit fermé
*/
void	if_in_quote(t_token_info *info, char *quote, int *inquote)
{
	int	i;

	i = *(info->i);
	if (!*inquote)
	{
		*inquote = 1;
		*quote = info->line[i];
	}
	else if (info->line[i] == *quote)
	{
		*inquote = 0;
		*quote = '\0';
	}
}

char	*check_quote_and_create_token(t_token_info *info, \
									int i, int inquote, char *quote)
{
	if (inquote == 1 && info->line[i] == '\0')
	{
		if (is_all_quotes_closed(info->line))
		{
			*(info->i) = i;
			return (add_token_word(info->i, info->start, \
							info->line, info->token));
		}
		info->line = read_until_quote_closed(info->line, *quote);
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
	add_token_end(token, create_token(WORD, str));
	return (line);
}
