/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_continuation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 11:43:24 by npederen          #+#    #+#             */
/*   Updated: 2025/08/02 13:55:04 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	is_printable_str(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (!isprint((unsigned char)s[i]) && !isspace((unsigned char)s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	continuation_child(const char *prompt, t_continuation_info *cinfo,\
															t_token_info *info)
{
	char	*line;

	setup_signal_heredoc();
	close(cinfo->fd[0]);
	line = readline(prompt);
	if (!line)
	{
		free_heredoc(info->line, NULL, info->token, info->env);
		ft_fprintf(2, "bash: syntax error: unexpected end of file\n");
		close(cinfo->fd[1]);
		exit(130);
	}
	else
	{
		write(cinfo->fd[1], line, ft_strlen(line));
		write(cinfo->fd[1], "\n", 1);
		free_heredoc(info->line, NULL, info->token, info->env);
		free_then_setnull((void **)&line);
		close(cinfo->fd[1]);
		exit(0);
	}
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
		free_then_setnull((void **)&cinfo->line);
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
		free_then_setnull((void **)&cinfo->line);
		return (NULL);
	}
	return (cinfo->line);
}

char	*readline_continuation(const char *prompt, t_token_info *info)
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
		continuation_child(prompt, &cinfo, info);
	return (continuation_parent(&cinfo, info->env));
}
