/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:34:39 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/28 18:53:33 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

char	*open_heredoc(t_token_info *info)
{
	char	*token_doc;
	char	*heredoc_line;
	int		j;
	char	*clean_quote;

	heredoc_line = NULL;
	token_doc = NULL;
	j = create_token_op_heredoc(info->line, info->i, info->token);
	while (info->line[*(info->i)] == ' ' && info->line[*(info->i)] != '\0')
		(*(info->i))++;
	info->start = *(info->i);
	if (info->line[*(info->i)] == '\0' || is_word(info->line[*(info->i)]) == 0)
		return (info->line);
	while (info->line[*(info->i)] != '\0'
		&& is_word(info->line[*(info->i)]) == 1
		&& info->line[*(info->i)] != ' ')
		(*(info->i))++;
	token_doc = ft_substr(info->line, info->start, *(info->i) - info->start);
	if (!token_doc)
		return (free(info->line), NULL);
	clean_quote = delete_quote(token_doc, info->token);
	heredoc_line = newline_heredoc(clean_quote, j, info->token, info->env);
	if (!heredoc_line || info->env->exit_code == 130)
	{
		free_token(*(info->token));
		*(info->token) = NULL;
		return (NULL);
	}
	add_token_end(info->token, create_token(INSIDE_HERE_DOC, heredoc_line));
	return (info->line);
}

char	*newline_heredoc(char *token_doc, int j, t_token **token, t_ctx *ctx)
{
	t_heredoc_info	hd;

	ft_memset(&hd, 0, sizeof(hd));
	pipe(hd.fd);
	hd.pid = fork();
	if (hd.pid == -1)
	{
		close(hd.fd[0]);
		close(hd.fd[1]);
		return (perror("fork"), NULL);
	}
	if (hd.pid == 0)
	{
		hd.line_error = 1;
		setup_signal_heredoc();
		close(hd.fd[0]);
		hd.line = ft_strdup("");
		while (1)
		{
			hd.next_line = readline("> ");
			if (!hd.next_line)
			{
				ft_fprintf(2,
					"minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n",
					hd.line_error, token_doc);
				write(hd.fd[1], hd.line, ft_strlen(hd.line));
				free_heredoc(hd.line, token_doc, token, ctx);
				close(hd.fd[1]);
				exit(0);
			}
			if (ft_strcmp(hd.next_line, token_doc) == 0)
			{
				free(hd.next_line);
				write(hd.fd[1], hd.line, ft_strlen(hd.line));
				break ;
			}
			hd.next_line = delete_tab_or_ad_return_line(hd.next_line, j);
			hd.buffer = ft_strjoin(hd.line, hd.next_line);
			free(hd.line);
			free(hd.next_line);
			if (!hd.buffer)
				exit(1);
			hd.line = hd.buffer;
			hd.line_error++;
		}
		free_heredoc(hd.line, token_doc, token, ctx);
		close(hd.fd[1]);
		exit(0);
	}
	else
	{
		setup_signals();
		close(hd.fd[1]);
		hd.heredoc_line = ft_strdup("");
		if (!hd.heredoc_line)
		{
			close(hd.fd[0]);
			return (NULL);
		}
		while ((hd.bytes = read(hd.fd[0], hd.tmp, sizeof(hd.tmp) - 1)) > 0)
		{
			hd.tmp[hd.bytes] = '\0';
			hd.buffer = ft_strjoin(hd.heredoc_line, hd.tmp);
			free(hd.heredoc_line);
			if (!hd.buffer)
			{
				close(hd.fd[0]);
				return (NULL);
			}
			hd.heredoc_line = hd.buffer;
		}
		close(hd.fd[0]);
		waitpid(hd.pid, &hd.status, 0);
		if (WIFSIGNALED(hd.status) || WEXITSTATUS(hd.status) == 130)
		{
			ctx->exit_code = 130;
			free(token_doc);
			free(hd.heredoc_line);
			return (NULL);
		}
		else if (WIFEXITED(hd.status))
		{
			ctx->exit_code = WEXITSTATUS(hd.status);
			if (ctx->exit_code == 130)
			{
				free(token_doc);
				free(hd.heredoc_line);
				return (NULL);
			}
		}
		else
			ctx->exit_code = 1;
		free(token_doc);
		return (hd.heredoc_line);
	}
}
