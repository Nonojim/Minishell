/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:34:39 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/20 02:40:42 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*open_heredoc(int *i, int start, char *line, t_token **token);
char	*newline_heredoc(char *token_doc, int j);
char	*found_delimiter(char *line, int *i);

int		create_token_op_heredoc(char *line, int *i, int start, t_token **token)
{
	char *str;
	int		j;

	(*i) += 2;
	if (line[*i] == '-') // = <<- = delete tab
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
	return(j);
}


/*
A rajouter . ( token <<- )
$ bash << EOF = exe dans un sous shell
> echo ok && echo yes 
> EOF
ok
yes
$ << EOF
> echo ok && echo yes
> EOF
Historique  Ne pas afficher Heredocument dans l historique afin d eviter de save des donnees comprometante
Dans n imrpote quelle cas expqnsion des vqriqble. SAUF: si <<'DELIMITATEUR' 
*/
char	*open_heredoc(int *i, int start, char *line, t_token **token)
{
	//char	*str;
	char	*next_line;
	char	*token_doc;
	char	*tmp;
	char	*heredoc_line = NULL;
	int		j;
	int		size_line;

	token_doc = NULL;
	heredoc_line = ft_strdup("");
	j = create_token_op_heredoc(line, i, start, token);
	size_line = 0;
	/*(*i) += 2;
	if (line[*i] == '-') // = <<- = delete tab
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
	}*/
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	start = *i;
	//si here doc sans mot aprés = non ouverture de la readline, mais on conserve le reste de la ligne
	if (line[*i] == '\0'|| is_word(line[*i]) == 0)
	{
		free(heredoc_line);
		return(line);
	}
	while (line[*i] != '\0' && is_word(line[*i]) == 1)
		(*i)++;
	token_doc = ft_substr(line, start, *i - start);
	if (!token_doc)
	{
		//free(token_doc);
		//free(heredoc_line);
		free(line);
		return (NULL);
	}
	//TOken delimitateur 
	//add_token_end(token, create_token(START_DELIMITATEUR, ft_strdup("START")));
	size_line = ft_strlen(token_doc) + 1;
	while (1)
	{
		next_line = readline("> ");
		if (!next_line)
			break ;
		if (ft_strncmp(next_line, token_doc, size_line) == 0)
		{
			free(next_line);
			break ;
		}
		tmp = ft_strjoin(heredoc_line, next_line);
		free(heredoc_line);
		heredoc_line = tmp;
		if (j == 1)
		{
			tmp = ft_strjoin(heredoc_line, "\n");
			free(heredoc_line);
			heredoc_line = tmp;
		}
		free(next_line);
	}
	add_token_end(token, create_token(INSIDE_HERE_DOC, heredoc_line));
	free(token_doc);
	//free(heredoc_line);
	return (line);
}

t_token	*tokenize_after_here_doc(t_token *token, char *line)
{
	//int	i = 0;
//	int		start;
	//char	*line_ptr;

	//line_ptr = line;
/*	while (line[i] != '\0')
	{
		while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'
				|| line[i] == '\n'))
			i++;
		//start = i;
		//tokenize2(&i, start, line, &token);
	}*/
	//line = line_ptr;
	add_token_end(&token, create_token(WORD, line));
	return (token);
}
