/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_bracket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:30:49 by npederen          #+#    #+#             */
/*   Updated: 2025/06/18 21:40:56 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	count_matching_bracket(char *str)
{
	int	left_bracket;
	int	right_bracket;

	left_bracket = 0;
	right_bracket = 0;
	while (*str)
	{
		if (*str == '(')
			left_bracket++;
		if (*str == ')')
			right_bracket++;
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
	int		ix ;

	ix = 0;
	while (count_matching_bracket(line) == 1)
		line = token_bracket_unclose(line);
	str = ft_substr(line, start, 1);
	add_token_end(token, create_token(BRACKETS_L, str));
	(*i)++;
	ix_start_bracket = *i;
	while (line[*i] && line [*i + 1] == ')')
	{
		(*i)++;
		while ((line[ix++] == '(' || line[*i] != ')') && line[*i])
			(*i)++;
	}
	ix_end_bracket = *i;
	str = ft_substr(line, ix_start_bracket, ix_end_bracket - ix_start_bracket);
	tokenize(*token, &str);
	free(str);
	/*if (!line[*i])
	{
		line = token_bracket_unclose(line);
		ft_strchr(line + start, ')');
	}*/
	return (line);
}
