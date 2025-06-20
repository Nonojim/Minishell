/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_heredoc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:20:24 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/20 14:25:11 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	create_token_op_heredoc(char *line, int *i, int start, t_token **token)
{
	char	*str;
	int		j;

	(*i) += 2;
	if (line[*i] == '-')
	{
		(*i)++;
		str = ft_substr(line, start, *i - start);
		add_token_end(token, create_token(HERE_DOC_DELETE_TAB, str));
		j = 0;
	}
	else
	{
		str = ft_substr(line, start, *i - start);
		add_token_end(token, create_token(HERE_DOCUMENT, str));
		j = 1;
	}
	return (j);
}

/*
* Faire un tab dabs le terminal : CTRL+V puis TAB
*/
char	*newline_heredoc(char *token_doc, int j)
{
	char	*next_line;
	char	*heredoc_line;
	char	*tmp;
	int		size_line;

	heredoc_line = ft_strdup("");
	size_line = ft_strlen(token_doc) + 1;
	while (1)
	{
		next_line = readline("> ");
		if (!next_line)
			break ;
		if (ft_strncmp(next_line, token_doc, size_line) == 0)
			return (free(next_line), heredoc_line);
		next_line = delete_tab_or_ad_return_line(next_line, j);
		tmp = ft_strjoin(heredoc_line, next_line);
		free(heredoc_line);
		heredoc_line = tmp;
		free(next_line);
	}
	return (heredoc_line);
}

char	*delete_tab_or_ad_return_line(char *next_line, int j)
{
	char	*tmp;
	int		k;

	k = 0;
	if (j == 0)
	{
		k = 0;
		while (next_line[k] == '\t')
			k++;
		tmp = ft_strdup(next_line + k);
		free(next_line);
		next_line = tmp;
	}
	tmp = ft_strjoin(next_line, "\n");
	free(next_line);
	return (tmp);
}

char	*delete_quote(char *str)
{
	char	*no_quote;
	int		i;

	if (!str)
		return (NULL);
	i = ft_strlen(str);
	if ((str[0] == '\'' && str[i - 1] == '\'')
		|| (str[0] == '"' && str[i - 1] == '"'))
		no_quote = ft_substr(str, 1, i - 2);
	else
		no_quote = ft_strdup(str);
	return (no_quote);
}

void	add_heredoc_token(t_token **token, char *token_doc, char *heredoc_line)
{
	char	*tmp;
	char	*quote;

	if (token_doc[0] == '\'' || token_doc[0] == '"')
	{
		tmp = ft_strjoin("\'", heredoc_line);
		quote = ft_strjoin(tmp, "\'");
		free(tmp);
		free(heredoc_line);
		add_token_end(token, create_token(QUOTE_HERE_DOC, quote));
	}
	else
		add_token_end(token, create_token(INSIDE_HERE_DOC, heredoc_line));
	free(token_doc);
}
