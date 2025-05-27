/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator_incomplete.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:36:54 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/27 16:11:24 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 * Utils for token_logical_incomplete
 * When the prompt finish by && or || with multiple space
 */
int	only_spaces_after_operator_logical(char *line, int i)
{
	i += 2;
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

/*
 * When the prompt finish by && or ||
 * MISS : plusieurs espace apres le && ou le ||
 */
char	*token_logical_incomplete(int *i, int start, char *line, t_token **token)
{
	char	*next_line; //ligne suivante dans readline
	char	*tmp; //tmp pour concatener
	char	*tmp_newline; //tmp pour contacatener

	if (only_spaces_after_operator_logical(line, *i))
	{
		while (1)
		{
			next_line = readline(" > ");
			if (!next_line)
				break ;
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
* MISS = modifier le cpt lors que des ";" sont add pour reproduire le cpt de bash notre minishell les prend en token
SOLUTION = différencier les ";" ajouté automatiquement et ceux ajouter par l'useur.
Pour cela = ajout d'un commentaire invisible avant le rajout du ';'(exemple \001, \x01 etc dans le tokenizer on verifie ce qu'il est pour l'ignorer dans le tokenizer ! Le probleme tout les caracteres invisible sont interprété par readline donc ca ne fonctionne pas vraiment.
Solution actuelle : création d'un history_line qui redisplay une ligne avec les ";" dans l'historique mais présence encore de l'ancienne ligne..... donc necessité de faire 2 fois fleches du haut.... 
*/
char	*token_bracket_incomplete(char *line)
{
	char	*next_line;
	char	*tmp;
	char	*history_line;

	history_line = ft_strdup(line);
	rl_clear_history();
	while (1)
	{
		next_line = readline("> ");
		if (!next_line)
			break ;
		tmp = ft_strjoin(line, "\n");
		free(line);
		line = tmp;
		tmp = ft_strjoin(history_line, "; ");
		free(history_line);
		history_line = tmp;
		tmp = ft_strjoin(history_line, next_line);
		free(history_line);
		history_line = tmp;
		tmp = ft_strjoin(line, next_line);
		free(line);
		line = tmp;
		free(next_line);
		if (ft_strchr(line, ')'))
			break ;
	}
	add_history(history_line);
	free(history_line);
	return (line);
}

char	*token_bracket(int *i, int start, char *line, t_token **token)
{
	char	*str;
	int		ix_start_bracket;
	int		ix_end_bracket;

	str = ft_substr(line, start, 1);
	add_token_end(token, create_token(BRACKETS_R, str));
	(*i)++;
	if (!ft_strchr(line + *i, ')'))
		line = token_bracket_incomplete(line);
	ix_start_bracket = *i;
	while (line[*i] && line[*i] != ')')
		(*i)++;
	ix_end_bracket = *i;
	str = ft_substr(line, ix_start_bracket, ix_end_bracket - ix_start_bracket);
	tokenize(*token, &str);
	free(str);
	if (!line[*i])
	{
		line = token_bracket_incomplete(line);
		ft_strchr(line + start, ')');
	}
	return (line);
}
