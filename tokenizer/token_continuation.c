/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_continuation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 11:43:24 by npederen          #+#    #+#             */
/*   Updated: 2025/08/01 12:21:20 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	continuation_child(const char *prompt, t_continuation_info *cinfo, t_ctx *ctx)
{
	char	*line;
	(void)ctx;
	setup_signal_heredoc();
	close(cinfo->fd[0]);
	line = readline(prompt);
	if (!line)
		exit(130); // signale une interruption comme Bash
	write(cinfo->fd[1], line, ft_strlen(line));
	write(cinfo->fd[1], "\n", 1);
	free(line);
	close(cinfo->fd[1]);
	exit(0);
}

char	*continuation_parent(t_continuation_info *cinfo, t_ctx *ctx)
{
	char	tmp[1024];
	int		bytes;

	close(cinfo->fd[1]);
	cinfo->line = ft_strdup("");
	if (!cinfo->line)
		return (close(cinfo->fd[0]), NULL);
	bytes = read(cinfo->fd[0], tmp, sizeof(tmp) - 1);
	while (bytes > 0)
	{
		tmp[bytes] = '\0';
		cinfo->buffer = ft_strjoin(cinfo->line, tmp);
		free(cinfo->line);
		if (!cinfo->buffer)
			return (close(cinfo->fd[0]), NULL);
		cinfo->line = cinfo->buffer;
		bytes = read(cinfo->fd[0], tmp, sizeof(tmp) - 1);
	}
	close(cinfo->fd[0]);
	waitpid(cinfo->pid, &cinfo->status, 0);
	if (WIFSIGNALED(cinfo->status) || WEXITSTATUS(cinfo->status) == 130)
	{
		ctx->exit_code = 130;
		free(cinfo->line);
		return (NULL);
	}
	return (cinfo->line);
}

char	*readline_continuation(const char *prompt, t_ctx *ctx)
{
	t_continuation_info	cinfo;

	ft_memset(&cinfo, 0, sizeof(cinfo));
	if (pipe(cinfo.fd) == -1)
		return (perror("pipe"), NULL);
	cinfo.pid = fork();
	if (cinfo.pid == -1)
	{
		close(cinfo.fd[0]);
		close(cinfo.fd[1]);
		return (perror("fork"), NULL);
	}
	if (cinfo.pid == 0)
		continuation_child(prompt, &cinfo, ctx);
	return (continuation_parent(&cinfo, ctx));
}
