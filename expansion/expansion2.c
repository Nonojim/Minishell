/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:12:57 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/24 12:44:49 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

/*
On traite les strings pour remplacer les vars d'environnement,
le tilde. On vérifie que les quotes sont ok avec ça.
On return les expansions appliqués
*/
char	*expand_string(char *str, t_treenode *node, t_ctx *ctx, \
										int wildcard_index)
{
	char	*result;
	char	*tmp;
	int		i;

	i = 0;
	if (!ft_strchr(str, '$') && !ft_strchr(str, '*') && str[0] != '~')
		return (ft_strdup(str));
	if (str[0] == '~' && str[i + 1] == '\0')
	{
		tmp = expand_tilde(str, ctx);
		return (tmp);
	}
	if (ft_strchr(str, '*') && (!node || node->type != HERE_DOCUMENT))
	{
		tmp = expand_wildcard(str, node, ctx, wildcard_index);
		return (tmp);
	}
	result = ft_strdup("");
	result = shearch_and_add_var(str, result, ctx);
	return (result);
}

char	*shearch_and_add_var(char *str, char *result, t_ctx *ctx)
{
	t_quote_state	q;
	int				i;

	i = 0;
	q.in_single_quote = 0;
	q.in_double_quote = 0;
	while (str[i])
	{
		if (toggle_quote(str, &i, &q, &result))
			continue ;
		if (!q.in_single_quote && str[i] == '$'
			&& (ft_isalpha(str[i + 1]) || str[i + 1] == '_'
				|| str[i + 1] == '?'))
		{
			i = expand_variable(str, i, &result, ctx);
			continue ;
		}
		add_char_to_string(&result, str[i]);
		i++;
	}
	return (result);
}

char	*expand_heredoc(char	*str, t_ctx *ctx)
{
	char	*result;
	int		i;

	if (!ft_strchr(str, '$'))
		return (ft_strdup(str));
	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalpha(str[i + 1])
				|| str[i + 1] == '_' || str[i + 1] == '?'))
		{
			i = expand_variable(str, i, &result, ctx);
			continue ;
		}
		add_char_to_string(&result, str[i]);
		i++;
	}
	return (result);
}

char	*expand_tilde(char *str, t_ctx *ctx)
{
	char	*home;
	char	*new_str;
	char	*result;

	home = ft_getenv("HOME", ctx);
	if (!home)
		return (NULL);
	new_str = ft_strdup(str + 1);
	result = ft_strjoin(home, new_str);
	free(new_str);
	return (result);
}

/*
Expanse une var d'environnement, 
Gere le code retour error $? 
*/
int	expand_variable(char *str, int i, char **result, t_ctx *ctx)
{
	int		j;
	char	*new_str;
	char	*expanse;
	char	*tmp;

	if (str[i + 1] == '?')
	{
		expanse = ft_itoa(ctx->exit_code);
		tmp = *result;
		*result = ft_strjoin(tmp, expanse);
		free(tmp);
		free(expanse);
		return (i + 2);
	}
	j = i + 1;
	while (str[j] != '\0' && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	new_str = ft_substr(str, i + 1, j - (i + 1));
	expanse = ft_getenv(new_str, ctx);
	if (!expanse)
		expanse = ("");
	free(new_str);
	tmp = *result;
	*result = ft_strjoin(tmp, expanse);
	free(tmp);
	return (j);
}
