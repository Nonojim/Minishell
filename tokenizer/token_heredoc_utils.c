/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_heredoc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:29:08 by lduflot           #+#    #+#             */
/*   Updated: 2025/08/01 17:51:53 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

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

void	free_heredoc(char *line, char *token_doc, t_token **token, t_ctx *ctx)
{
	if (line)
	{
		free(line);
		line = NULL;
	}
	if (token_doc)
	{
		free(token_doc);
		token_doc = NULL;
	}
	if (token)
	{
		free_token(*token);
		*token = NULL;
	}
	if (ctx)
		free_env_list(ctx->env);
}
