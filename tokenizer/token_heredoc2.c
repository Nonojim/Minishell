/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_heredoc2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:58:47 by lduflot           #+#    #+#             */
/*   Updated: 2025/08/06 11:07:39 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	heredoc_child_process(t_heredoc_info *hd, char *token_doc, \
									t_token **token, t_ctx *ctx)
{
	hd->line_error = 1;
	setup_signal_heredoc();
	close(hd->fd[0]);
	hd->line = ft_strdup("");
	heredoc_loop(hd, token_doc, token, ctx);
	free_heredoc(hd->line, token_doc, token, ctx);
	close(hd->fd[1]);
	exit(0);
}

void	heredoc_loop(t_heredoc_info *hd, char *token_doc, \
									t_token **token, t_ctx *ctx)
{
	while (1)
	{
		hd->next_line = readline("> ");
		if (!hd->next_line)
			heredoc_eof(hd, token_doc, token, ctx);
		if (ft_strcmp(hd->next_line, token_doc) == 0)
		{
			free(hd->next_line);
			write(hd->fd[1], hd->line, ft_strlen(hd->line));
			break ;
		}
		hd->next_line = delete_tab_or_ad_return_line(hd->next_line, hd->j);
		hd->buffer = ft_strjoin(hd->line, hd->next_line);
		free(hd->line);
		free(hd->next_line);
		if (!hd->buffer)
			exit(1);
		hd->line = hd->buffer;
		hd->line_error++;
	}
}

void	heredoc_eof(t_heredoc_info *hd, char *token_doc, \
							t_token **token, t_ctx *ctx)
{
	ft_fprintf(2,
		"minishell: warning: here-document at line %d \
delimited by end-of-file (wanted `%s')\n",
		hd->line_error, token_doc);
	write(hd->fd[1], hd->line, ft_strlen(hd->line));
	free_heredoc(hd->line, token_doc, token, ctx);
	close(hd->fd[1]);
	exit(0);
}

char	*heredoc_parent_process(t_heredoc_info *hd, char *token_doc, t_ctx *ctx)
{
	setup_signals();
	close(hd->fd[1]);
	hd->heredoc_line = ft_strdup("");
	if (!hd->heredoc_line)
		return (close(hd->fd[0]), NULL);
	hd->bytes = read(hd->fd[0], hd->tmp, sizeof(hd->tmp) - 1);
	while (hd->bytes > 0)
	{
		hd->tmp[hd->bytes] = '\0';
		hd->buffer = ft_strjoin(hd->heredoc_line, hd->tmp);
		free(hd->heredoc_line);
		if (!hd->buffer)
			return (close(hd->fd[0]), NULL);
		hd->heredoc_line = hd->buffer;
		hd->bytes = read(hd->fd[0], hd->tmp, sizeof(hd->tmp) - 1);
	}
	close(hd->fd[0]);
	if (!check_heredoc_exit_status(hd, token_doc, ctx))
		return (NULL);
	free(token_doc);
	return (hd->heredoc_line);
}

int	check_heredoc_exit_status(t_heredoc_info *hd, char *token_doc, t_ctx *ctx)
{
	waitpid(hd->pid, &hd->status, 0);
	if (WIFSIGNALED(hd->status) || WEXITSTATUS(hd->status) == 130)
	{
		ctx->exit_code = 130;
		free(token_doc);
		free(hd->heredoc_line);
		return (0);
	}
	else if (WIFEXITED(hd->status))
	{
		ctx->exit_code = WEXITSTATUS(hd->status);
		if (ctx->exit_code == 130)
		{
			free(token_doc);
			free(hd->heredoc_line);
			return (0);
		}
	}
	else
		ctx->exit_code = 1;
	return (1);
}
