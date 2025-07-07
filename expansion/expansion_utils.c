/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:55:13 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/07 16:45:50 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*ft_getenv(char *name, t_ctx *ctx)
{
	t_env	*usrvar;

	usrvar = find_usrvar(ctx->env, name);
	if (!usrvar)
		return (ft_strdup(""));
	return (ft_strdup(usrvar->value));
}

/* Les deux premiers blocs if = TOGGLE QUOTES
			* Deux flags : double, single
			* Si on lit un ' et qu'on est pas déjà dans un double alors 
			* on ouvre ou ferme un bloc de quote simple.
*/
int	toggle_quote(char *str, int *i, t_quote_state *q, char **result)
{
	char	quote;
	char	*new_str;
	char	*tmp;

	quote = str[*i];
	if ((quote == '\'' && !q->in_double_quote)
		|| (quote == '"' && !q->in_single_quote))
	{
		if (quote == '\'')
			q->in_single_quote = !(q->in_single_quote);
		else
			q->in_double_quote = !(q->in_double_quote);
		new_str = ft_substr(str, *i, 1);
		tmp = *result;
		*result = ft_strjoin(tmp, new_str);
		free(tmp);
		free(new_str);
		(*i)++;
		return (1);
	}
	return (0);
}

char	*remove_quotes_after_expansion(const char *str)
{
	char	*new;
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	if (!str)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && quote == 0)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}
