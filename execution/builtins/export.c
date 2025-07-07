/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:28:25 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/07 15:39:02 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_export(t_treenode *node, t_ctx *ctx)
{
	int		i;

	i = 0;
	if (node->argv[i + 1] == NULL)
	{
		print_export(ctx->env);
		return (0);
	}
	while (node->argv[i])
	{
		add_export_variable(ctx, node->argv[i]);
		i++;
	}
	return (0);
}

void	add_export_variable(t_ctx *ctx, char *arg)
{
	int		j;
	int		value_len;
	char	*key;
	char	*value;

	j = 0;
	while (arg[j] && arg[j] != '=')
		j++;
	if (arg[j] == '=')
	{
		key = ft_substr(arg, 0, j);
		value_len = ft_strlen(arg) - j - 1;
		value = ft_substr(arg, j + 1, value_len);
		export_to_env(&ctx->env, key, value);
		free(key);
		free(value);
	}
}

void	print_export(t_env *env)
{
	t_env	*tmp;
	t_env	*copy;
	copy = copy_env(env);
	ft_sort_env_list(copy);
	tmp = copy;
	while (tmp->next)
	{
		if (tmp->value && ft_strcmp(tmp->key, "?") != 0)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	free_env_list(copy);
}

t_env	*copy_env(t_env *env)
{
	t_env	*new = NULL;
	t_env	*tmp = env;
	t_env	*node;

	while (tmp)
	{
		node = malloc(sizeof(t_env));
		if (!node)
			return (free_env_list(new), NULL);

		node->key = strdup(tmp->key);
		node->value = strdup(tmp->value);
		node->next = NULL;
		ft_env_add_back(&new, node);
		tmp = tmp->next;
	}
	return (new);
}

void	ft_env_add_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst || !new)
		return;
	if (!*lst)
	{
		*lst = new;
		return;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_sort_env_list(t_env *env)
{
	t_env	*tmp;
	t_env	*start;
	char	*key_tmp;
	char	*value_tmp;

	if (!env)
		return;

	start = env;
	tmp = env;
	while (tmp && tmp->next)
	{
		if (ft_strcmp(tmp->key, tmp->next->key) > 0)
		{
			key_tmp = tmp->key;
			tmp->key = tmp->next->key;
			tmp->next->key = key_tmp;
			value_tmp = tmp->value;
			tmp->value = tmp->next->value;
			tmp->next->value = value_tmp;
			tmp = start;
		}
		else
			tmp = tmp->next;
	}
}
