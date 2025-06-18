/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator_incomplete.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:36:54 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/18 21:10:21 by npederen         ###   ########.fr       */
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
 */
char	*token_logical_unclose(int *i, int start, char *line, t_token **token)
{
	char	*next_line;
	char	*tmp;
	char	*tmp_newline;

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

int	only_spaces_after_pipe(char *line, int i)
{
	i++;
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

char	*token_pipe_unclose(int *i, int start, char *line, t_token **token)
{
	char	*next_line;
	char	*tmp;
	char	*tmp_newline;

	if (only_spaces_after_pipe(line, *i))
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
* MISS = new line = ajout ';'
* SOLUTION = différencier les ";" ajouté automatiquement et ceux ajouter useur.
Pour cela = ajout d'un commentaire invisible avant le rajout 
du ';'(exemple \001, \x01 etc dans le tokenizer 
on verifie ce qu'il est pour l'ignorer dans le tokenizer ! 
Le probleme tout les caracteres invisible sont interprété par readline 
donc ca ne fonctionne pas vraiment.
Solution actuelle : création d'un history_line qui redisplay une ligne avec 
les ";" 
dans l'historique mais présence encore de l'ancienne ligne..... 
donc necessité de faire 2 fois fleches du haut....
*/

char	*token_bracket_unclose(char *line)
{
	char	*next_line;
	char	*history_line;

	history_line = ft_strdup(line);
	rl_clear_history();
	while (1)
	{
		next_line = readline("> ");
		if (!next_line)
			break ;
		bracket_unclosed(&line, &history_line, next_line);
		free(next_line);
		if (ft_strchr(line, ')'))
			break ;
	}
	add_history(history_line);
	free(history_line);
	return (line);
}

void	bracket_unclosed(char **line, char **history_line, char*next_line)
{
	char	*tmp;

	tmp = ft_strjoin(*line, "\n");
	free(*line);
	*line = tmp;
	tmp = ft_strjoin(*history_line, "; ");
	free(*history_line);
	*history_line = tmp;
	tmp = ft_strjoin(*history_line, next_line);
	free(*history_line);
	*history_line = tmp;
	tmp = ft_strjoin(*line, next_line);
	free(*line);
	*line = tmp;
}

int	count_matching_bracket(char *str)
{
	int	left_bracket;
	int	right_bracket;

	left_bracket = 0;
	right_bracket = 0;
	while (*str)
	{
		if (*str == '(' || *str == ')')
		{
			while (*str == '(')
			{
				left_bracket++;
				str++;
			}
			while (*str == ')')
			{
				right_bracket++;
				str++;
			}
		}
		else
			str++;
	}
	if (left_bracket <= right_bracket)
		return (0);
	else
		return (1);
}

char	*token_bracket(int *i, int start, char *line, t_token **token)
{
	char	*str;
	int		ix_start_bracket;
	int		ix_end_bracket;
	int		ix = 0;
	int		match;

	while ((match = count_matching_bracket(line)) == 1)
		line = token_bracket_unclose(line);
	str = ft_substr(line, start, 1);
	add_token_end(token, create_token(BRACKETS_L, str));
	(*i)++;
	ix_start_bracket = *i;
	while (line[*i] && line [*i + 1] == ')')
	{
		(*i)++;
		while ((line[ix] == '(' || line[*i] != ')') && line[*i])
		{
			(*i)++;
			ix++;
		}
	}	
	ix_end_bracket = *i;
	str = ft_substr(line, ix_start_bracket, ix_end_bracket - ix_start_bracket);
	tokenize(*token, &str);
	free(str);
	//if (!line[*i])
	//{
	//	line = token_bracket_unclose(line);
	//	ft_strchr(line + start, ')');
	//}
	return (line);
}
