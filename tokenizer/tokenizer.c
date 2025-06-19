/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:49:49 by npederen          #+#    #+#             */
/*   Updated: 2025/06/19 13:18:08 by lduflot          ###   ########.fr       */
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

t_token	*tokenize_after_here_doc(t_token *token, char *line)
{
	int	i = 0;
	int		start;

	while (line[i] != '\0')
	{
		while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'
				|| line[i] == '\n'))
			i++;
		start = i;
		tokenize2(&i, start, line, &token);
	}
	//*line_ptr = line;
	return (token);
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
//	char	doc;
	char *str;
	char	*next_line;
	char	*token_doc = NULL;
	char *tmp;
	char	*heredoc_line = NULL;
//	doc = line[*i];
	(*i) += 2;
	if (line[*i] == '-') // = <<- = delete tab
	{
		(*i)++;
		str = ft_substr(line, start, *i - start);
		add_token_end(token, create_token(HERE_DOC_DELETE_TAB, str));
		//if (line[*i + 1] != '\0')
			//(*i)++;
	}
	else
	{
		str = ft_substr(line, start, *i - start);
		add_token_end(token, create_token(HERE_DOCUMENT, str));
	}
	//printf("line = %c\n", line[*i]);
		
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	start = *i;
	//si here doc sans mot aprés = non ouverture de la readline, mais on conserve le reste de la ligne
	if (line[*i] == '\0'|| is_word(line[*i]) == 0)
		return(line);
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
	//met en token les delimitateurs
	//add_token_end(token, create_token(WORD, token_doc));
	int size_line = ft_strlen(token_doc) + 1;

	while (1)
	{
		next_line = readline("> ");
		if (!next_line)
			break ;
		//printf("line : %s, token_doc %s \n", line, token_doc);
		if (ft_strncmp(next_line, token_doc, size_line) == 0)
		{
			free(next_line);
			break ;
		}
		tmp = ft_strjoin(heredoc_line, next_line);
		//printf("tmp = %s, line = %s", tmp, line);
		free(heredoc_line);
		heredoc_line = tmp;
		tmp = ft_strjoin(heredoc_line, "\n");
		free(heredoc_line);
		heredoc_line = tmp;
		free(next_line);
	}
	tokenize_after_here_doc(*token, line);
	free(token_doc); //1H A TROUVER CE FREE POUR 1 LEAK 
	free(heredoc_line);
	//*tokenize_after_here_doc(&token, &line, i);
	return (line);
}
