/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:34:39 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/20 14:26:20 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*open_heredoc(int *i, int start, char *line, t_token **token);
char	*newline_heredoc(char *token_doc, int j);
int		create_token_op_heredoc(char *line, int *i, int start, t_token **token);
char	*delete_tab_or_ad_return_line(char *next_line, int j);
void	add_heredoc_token(t_token **token, char *token_doc, char *heredoc_line);

char	*open_heredoc(int *i, int start, char *line, t_token **token)
{
	char	*token_doc;
	char	*heredoc_line;
	int		j;
	char	*clean_quote;

	heredoc_line = NULL;
	token_doc = NULL;
	j = create_token_op_heredoc(line, i, start, token);
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	start = *i;
	if (line[*i] == '\0' || is_word(line[*i]) == 0)
		return (line);
	while (line[*i] != '\0' && is_word(line[*i]) == 1)
		(*i)++;
	token_doc = ft_substr(line, start, *i - start);
	if (!token_doc)
		return (free(line), NULL);
	clean_quote = delete_quote(token_doc);
	heredoc_line = newline_heredoc(clean_quote, j);
	free(clean_quote);
	add_heredoc_token(token, token_doc, heredoc_line);
	return (line);
}
