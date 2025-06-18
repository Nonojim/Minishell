/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:49:49 by npederen          #+#    #+#             */
/*   Updated: 2025/06/18 22:19:38 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*open_heredoc(int *i, int start, char *line, t_token **token);

t_token	*tokenize(t_token *token, char **line_ptr)
{
	char	*line;
	int		start;
	int		i;

	line = *line_ptr;
	i = 0;
	start = 0;
	while (line[i] != '\0')
	{
		while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'
				|| line[i] == '\n'))
			i++;
		start = i;
		line = tokenize2(&i, start, line, &token);
	}
	*line_ptr = line;
	return (token);
}

char	*tokenize2(int	*i, int start, char *line, t_token **token)
{
	if ((line[*i] == '\'' || line[*i] == '\"') && line[*i])
		line = token_quote(i, start, line, token);
	else if ((line[*i] == '&' && line[*i + 1] == '&')
		|| (line[*i] == '|' && line[*i + 1] == '|'))
		line = token_logical_unclose(i, start, line, token);
	else if (line[*i] == '|')
		line = token_pipe_unclose(i, start, line, token);
	else if (line[*i] == '<' && line[*i + 1] == '<')
		line = open_heredoc(i, start, line, token);
	else if (line[*i] == '(' && line[*i])
		line = token_bracket(i, start, line, token);
	else if (line[*i] == '$')
		token_expansion(i, start, line, token);
	else if (is_operator_logical(line[*i]) == line[*i] && line[*i])
		token_logical_operator(i, start, line, token);
	else if (line[*i] != '\0' && is_word(line[*i]) == 1)
		token_word(i, start, line, token);
	return (line);
}

/*t_token	*tokenize_after_here_doc(t_token *token, char **line_ptr, int *i)
{
	char	*line;
	int		start;

	line = *line_ptr;
	start = 0;
	while (line[i] != '\0')
	{
		while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'
				|| line[i] == '\n'))
			i++;
		start = i;
		line = tokenize2(&i, start, line, &token);
	}
	*line_ptr = line;
	return (token);
}*/


char	*open_heredoc(int *i, int start, char *line, t_token **token)
{
//	char	doc;
	char *str;
	char	*next_line;
	char	*token_doc = NULL;
	char *tmp;

//	doc = line[*i];
	(*i) += 2;
	str = ft_substr(line, start, *i - start);
	add_token_end(token, create_token(HERE_DOCUMENT, str));
	while (line[*i] == ' ')
		(*i)++;
	start = *i;
	//printf("%s\n", line);
	//printf("str = %s\n", str);
	//(*i++);
	while (line[*i] != '\0' && is_word(line[*i]) == 1)
		(*i)++;
	token_doc = ft_substr(line, start, *i - start);
	if (!token_doc)
		return (NULL);
//	printf("token_doc1 : %s", token_doc);
	//printf("token_doc %s", token_doc);
	add_token_end(token, create_token(WORD, token_doc));
	int size_line = ft_strlen(token_doc) + 1;

	while (1)
	{
		next_line = readline("> ");
		if (!next_line)
			break ;
		//printf("line : %s, token_doc %s \n", line, token_doc);
		if (ft_strncmp(next_line, token_doc, size_line) == 0)
			break ;
		tmp = ft_strjoin(line, "\n");
		//printf("tmp = %s, line = %s", tmp, line);
		free(line);
		line = tmp;
		tmp = ft_strjoin(line, next_line);
		free(line);
		line = tmp;
		free(next_line);
		(*i)++;
	}
	//*tokenize_after_here_doc(&token, &line, i);
	return (line);
}
