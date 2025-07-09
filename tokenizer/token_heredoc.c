/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:34:39 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/09 15:36:11 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

char	*open_heredoc(int *i, int start, char *line, t_token **token, t_ctx *ctx);
char	*newline_heredoc(char *token_doc, int j, t_ctx *ctx);
int		create_token_op_heredoc(char *line, int *i, t_token **token);
char	*delete_tab_or_ad_return_line(char *next_line, int j);
void	add_heredoc_token(t_token **token, char *token_doc, char *heredoc_line);

char	*open_heredoc(int *i, int start, char *line, t_token **token, t_ctx *ctx)
{
	char	*token_doc;
	char	*heredoc_line;
	int		j;
	char	*clean_quote;

	heredoc_line = NULL;
	token_doc = NULL;
	j = create_token_op_heredoc(line, i, token);
	while (line[*i] == ' ' && line[*i] != '\0')
		(*i)++;
	start = *i;
	if (line[*i] == '\0' || is_word(line[*i]) == 0)
		return (line);
	while (line[*i] != '\0' && is_word(line[*i]) == 1)
		(*i)++;
	token_doc = ft_substr(line, start, *i - start);
	if (!token_doc)
		return (free(line), NULL);
	clean_quote = delete_quote(token_doc, token);
	heredoc_line = newline_heredoc(clean_quote, j, ctx);
	free(clean_quote);
	add_token_end(token, create_token(INSIDE_HERE_DOC, heredoc_line));
	printf("line : [%s]\n", line);
	return (line);
}

int	create_token_op_heredoc(char *line, int *i, t_token **token)
{
	int	j;

	(*i) += 2;
	if (line[*i] == '-')
	{
		(*i)++;
		j = 0;
	}
	else
		j = 1;
	if (line[*i] == '\0')
		add_token_end(token, create_token(HERE_DOCUMENT, ft_strdup(line)));
	return (j);
}

/*
* Faire un tab dabs le terminal : CTRL+V puis TAB
*/
char	*newline_heredoc(char *token_doc, int j, t_ctx *ctx)
{
	char	*line;
	char	*next_line;
	char	*heredoc_line;
	char	*buffer;
	char	tmp[1024];
	int		size_line;
	pid_t		pid;
	int		fd[2];
	int		status;
	ssize_t	bytes;

	pipe(fd);
	pid = fork();
	if (pid == -1)
		return (perror("error fork"), NULL);
	if (pid == 0)
	{
		line = ft_strdup("");
		setup_signal_heredoc();
		close(fd[0]);
		size_line = ft_strlen(token_doc);
		while (1)
		{
			next_line = readline("> ");
			if (!next_line)
			{
				write(fd[1], line, ft_strlen(line));
				//free(line);
				//free(token_doc);
				//free_env_list(ctx->env);
				break ;
			}
			if (ft_strncmp(next_line, token_doc, size_line) == 0)
			{
				free(next_line);
				write(fd[1], line, ft_strlen(line));
				//free_env_list(ctx->env);
				//free(token_doc);
				//free(line);
				break;
			}
			if (ft_strncmp(next_line, token_doc, size_line) != 0)
			{
				next_line = delete_tab_or_ad_return_line(next_line, j);
				buffer = line;
				line = ft_strjoin(line, next_line);
				free(buffer);
				free(next_line);
			}
		}
		free_env_list(ctx->env);
		free(token_doc);
		free(line);
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		setup_signals();
		close(fd[1]);
		heredoc_line = ft_strdup("");
		while ((bytes = read(fd[0], tmp, sizeof(tmp))) > 0)
		{
			tmp[bytes] = '\0';
			buffer = ft_strjoin(heredoc_line, tmp);
			free(heredoc_line);
			heredoc_line = buffer;
		}
		close(fd[0]);
		waitpid(pid, &status, 0);
		return (heredoc_line);
	}
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

char	*delete_quote(char *str, t_token **token)
{
	char	*no_quote;
	int		i;

	if (!str)
		return (NULL);
	add_token_end(token, create_token(HERE_DOCUMENT, ft_strdup(str)));
	i = ft_strlen(str);
	if ((str[0] == '\'' && str[i - 1] == '\'')
		|| (str[0] == '"' && str[i - 1] == '"'))
		no_quote = ft_substr(str, 1, i - 2);
	else
		no_quote = ft_strdup(str);
	free(str);
	return (no_quote);
}
