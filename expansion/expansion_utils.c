/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:55:13 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/30 14:10:51 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*ft_getenv(char *name, t_treenode *node)
{
	t_env	*node_env;

	node_env = find_node(node->env, name);
	if (!node_env)
		return (ft_strdup(""));
	return (ft_strdup(node_env->value));
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
