/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:34:39 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/29 12:16:02 by lduflot          ###   ########.fr       */
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
	while (info->line[*(info->i)] != '\0' && info->line[*(info->i)] != ' '
		&& is_word(info->line[*(info->i)]) == 1)
		(*(info->i))++;
	token_doc = ft_substr(info->line, info->start, *(info->i) - info->start);
	if (!token_doc)
		return (free(info->line), NULL);
	clean_quote = delete_quote(token_doc, info->token);
	heredoc_line = newline_heredoc(clean_quote, j, info->token, info->env);
	if (!heredoc_line || info->env->exit_code == 130)
		return (free_token(*(info->token)), *(info->token) = NULL, NULL);
	add_token_end(info->token, create_token(INSIDE_HERE_DOC, heredoc_line));
	return (info->line);
}

char	*newline_heredoc(char *token_doc, int j, t_token **token, t_ctx *ctx)
{
	t_heredoc_info	hd;

	ft_memset(&hd, 0, sizeof(hd));
	hd.j = j;
	pipe(hd.fd);
	hd.pid = fork();
	if (hd.pid == -1)
	{
		close(hd.fd[0]);
		close(hd.fd[1]);
		return (perror("fork"), NULL);
	}
	if (hd.pid == 0)
		heredoc_child_process(&hd, token_doc, token, ctx);
	return (heredoc_parent_process(&hd, token_doc, ctx));
}
