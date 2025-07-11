/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:05:41 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/11 15:26:18 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void	expanse_ast(t_treenode *node, t_ctx *ctx)
{
	int		i;
	char	*expanded;
	char	*clean;

	if (!node)
		return ;
	if (node->type == HERE_DOCUMENT)
	{
		if (node->str && (node->str[0] == '\'' || node->str[0] == '"'))
			return ;
		if (node->right && node->right->str)
		{
			char *expanded = expand_string(node->right->str, node, ctx);
			free(node->right->str);
			node->right->str = expanded;
		}
		return ;
	}
	if (node->argv)
	{
		i = 0;
		while (node->argv[i])
		{
			expanded = expand_string(node->argv[i], node, ctx);
			if (expanded == NULL)
			{
				clean = remove_quotes_after_expansion(node->argv[i]);
				free(node->argv[i]);
				node->argv[i] = clean;
				i++;
				continue ;
			}
			free(node->argv[i]);
			if ((expanded != NULL) && (ft_strchr(expanded, '\'') || ft_strchr(expanded, '"')))
			{
				clean = remove_quotes_after_expansion(expanded);
				free(expanded);
				node->argv[i] = clean;
			}
			else
				node->argv[i] = expanded;
			i++;
		}
	}
//	if(node->left)
//		expanse_ast(node->left, ctx);
//	if(node->right)
//		expanse_ast(node->right, ctx);
}

/*
On traite les strings pour remplacer les vars d'environnement,
le tilde. On vérifie que les quotes sont ok avec ça.
On return les expansions appliqués
*/
char	*expand_string(char *str, t_treenode *node, t_ctx *ctx)
{
	char			*result;
	char			*tmp;
	t_quote_state	q;
	int				i;

	i = 0;
	if (!ft_strchr(str, '$') && !ft_strchr(str, '*') && str[0] != '~')
		return (ft_strdup(str));
	if (str[0] == '~' && str[i + 1] == '\0')
	{
		tmp = expand_tilde(str, ctx);
		return(tmp);
	}
	if (ft_strchr(str, '*') && (!node || node->type != HERE_DOCUMENT))
	{
		tmp = expand_wildcard(str, node);
		return(tmp);
	}
	result = ft_strdup("");
	i = 0;
	q.in_single_quote = 0;
	q.in_double_quote = 0;
	while (str[i])
	{
		if (toggle_quote(str, &i, &q, &result))
			continue ;
		if (!q.in_single_quote && str[i] == '$'
			&& (ft_isalpha(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?'))
		{
			i = expand_variable(str, i, &result, ctx);
			continue ;
		}
		add_char_to_string(&result, str[i]);
		i++;
	}
	return (result);
}
	/*while (str[i])
	{
		if (toggle_quote(str, &i, &q, &result))
			continue ;
		if (!q.in_single_quote && !q.in_double_quote && str[0] == '~' && str[1] == '\0')
		{
			tmp = expand_tilde(str, ctx);
			if (tmp)
			{
				free(result);
				return (tmp);
			}
		}
		if (!q.in_single_quote && !q.in_double_quote && ft_strchr(str,'*'))
		{
			tmp = expand_wildcard(str, node);
			free(result);
			return(tmp);
			if (tmp)
			{
				free(result);
				return (tmp);
			}
		}
		if (!q.in_single_quote && str[i] == '$'
			&& (ft_isalpha(str[i + 1])
				|| str[i + 1] == '_' || str[i + 1] == '?'))
		{
			i = expand_variable(str, i, &result, ctx);
			continue ;
		}
		//LOGIQUE A REVOIR ! Renvoi la même string si pas d'expansion !!!
		add_char_to_string(&result, str[i]);
		i++;
	}
	return (result);*/

void	add_char_to_string(char **result, char c)
{
	char	*tmp;
	size_t	len;

	if (!result)
		return ;
	len = ft_strlen(*result);
	tmp = malloc(len + 2);
	if (!tmp)
		return ;
	ft_memcpy(tmp, *result, len);
	tmp[len] = c;
	tmp[len + 1] = '\0';
	if (result != NULL)
		free(*result);
	*result = tmp;
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
	free(new_str);
	tmp = *result;
	*result = ft_strjoin(tmp, expanse);
	free(tmp);
	return (j);
}
