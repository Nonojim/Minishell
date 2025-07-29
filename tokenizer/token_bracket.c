/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_bracket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:30:49 by npederen          #+#    #+#             */
/*   Updated: 2025/07/28 18:24:26 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	bracket_unclosed(char **line, char **history_line, char *next_line)
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

char	*token_bracket(t_token_info *info)
{
	char	*str;
	int		ix_start_bracket;
	int		ix_end_bracket;
	int		ix;

	ix = 0;
	while (count_matching_bracket(info->line) == 1)
		info->line = token_bracket_unclose(info->line);
	str = ft_substr(info->line, info->start, 1);
	add_token_end(info->token, create_token(BRACKETS_L, str));
	(*(info->i))++;
	ix_start_bracket = *(info->i);
	while (info->line[*(info->i)] && info->line[*(info->i) + 1] == ')')
	{
		(*(info->i))++;
		while ((info->line[ix++] == '(' || info->line[*(info->i)] != ')')
			&& info->line[*(info->i)])
			(*(info->i))++;
	}
	ix_end_bracket = *(info->i);
	str = ft_substr(info->line, ix_start_bracket, \
									ix_end_bracket - ix_start_bracket);
	tokenize(*(info->token), &str, info->env);
	free(str);
	return (info->line);
}
