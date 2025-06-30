/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:05:41 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/30 14:22:57 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*expand_tilde(char *str, t_treenode *node);
void	add_char_to_string(char **result, char c);

/*
On parcours l'ast récursivement et on expanse les arg
*/
void	expanse_ast(t_treenode *node)
{
	int		i;
	char	*new_arg;

	if (!node)
		return ;
	if (node->left)
		node->left->env = node->env;
	if (node->right)
		node->right->env = node->env;
	if (node->argv)
	{
		i = 0;
		while (node->argv[i])
		{
			new_arg = expand_string(node->argv[i], node);
			free(node->argv[i]);
			node->argv[i] = new_arg;
			i++;
		}
	}
	if (node->type == HERE_DOCUMENT)
	{
		i = 0;
		if (node->str[i] == '\'' || node->str[i] == '"')
			return ;
		else
		{
			while (node->argv && node->argv[i])
			{
				new_arg = expand_string(node->argv[i], node);
				free(node->argv[i]);
				node->argv[i] = new_arg;
				i++;
			}
		}
	}
	if (node->type == WORD && node->argv && node->argv[0])
	{
		free(node->str);
		node->str = ft_strdup(node->argv[0]);
	}
	expanse_ast(node->left);
	expanse_ast(node->right);
}

/*
On traite les strings pour remplacer les vars d'environnement,
le tilde. On vérifie que les quotes sont ok avec ça.
On return les expansions appliqués
*/
char	*expand_string(char *str, t_treenode *node)
{
	char			*result;
	char			*tmp;
	t_quote_state	q;
	int				i;

	result = ft_strdup("");
	i = 0;
	q.in_single_quote = 0;
	q.in_double_quote = 0;
	while (str[i])
	{
		if (toggle_quote(str, &i, &q, &result))
			continue ;
		if (!q.in_single_quote && !q.in_double_quote && str[i] == '~')
		{
			tmp = expand_tilde(str, node);
			if (tmp)
				return (tmp);
		}
		if (!q.in_single_quote && str[i] == '$'
			&& (ft_isalpha(str[i + 1])
				|| str[i + 1] == '_' || str[i + 1] == '?'))
		{
			i = expand_variable(str, i, &result, node);
			continue ;
		}
		add_char_to_string(&result, str[i]);
		i++;
	}
	return (result);
}

void	add_char_to_string(char **result, char c)
{
	char	*tmp;
	char	*to_add;

	to_add = ft_substr(&c, 0, 1);
	tmp = *result;
	*result = ft_strjoin(tmp, to_add);
	free(tmp);
	free(to_add);
}

char	*expand_tilde(char *str, t_treenode *node)
{
	char	*home;
	char	*new_str;
	char	*result;

	home = ft_getenv("HOME", node);
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
int	expand_variable(char *str, int i, char **result, t_treenode *node)
{
	int		j;
	char	*new_str;
	char	*expanse;
	char	*tmp;

	if (str[i + 1] == '?')
	{
		expanse = ft_getenv("?", node);
		if (!expanse)
			expanse = ft_strdup("0");
		tmp = *result;
		*result = ft_strjoin(tmp, expanse);
		free(tmp);
		free(expanse);
		return (i + 2);
	}
	j = i + 1;
	while (str[j] != '\0' && (ft_isalpha(str[j]) || str[j] == '_'))
		j++;
	new_str = ft_substr(str, i + 1, j - (i + 1));
	expanse = ft_getenv(new_str, node);
	free(new_str);
	tmp = *result;
	*result = ft_strjoin(tmp, expanse);
	free(tmp);
	free(expanse);
	return (j);
}
