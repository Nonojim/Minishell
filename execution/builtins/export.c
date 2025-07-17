/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:28:25 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/17 15:54:35 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_valid_export(char *arg)
{
	int	i = 0;

	while (arg[i] && arg[i] != '=')
	{
		if (!arg || (!ft_isalpha(arg[i]) && arg[i] != '-' && arg[0] != '~'))
			return (0);
		i++;
	}
	
	return (1);
}

int	ft_export(t_treenode *node, t_ctx *ctx)
{
	int		i;
	i = 0;
	if (node->argv[i + 1] == NULL)
	{
		print_export(ctx->env);
		return (0);
	}
	i = 1;
	while (node->argv[i])
	{
		//printf("%s\n", node->argv[i]);
		add_export_variable(ctx, node->argv[i]);
		i++;
	}
	return (ctx->exit_code);
}

void	add_export_variable(t_ctx *ctx, char *arg)
{
	int		j;
	int		value_len;
	char	*key;
	char	*value;

	j = 0;
	if (!is_valid_export(arg))
	{
		ft_fprintf(2, "minishell: export: `%s': not a valid identifier\n", arg);
		ctx->exit_code = 1;
		return;
	}
	while (arg[j] && arg[j] != '=')
		j++;
	key = ft_substr(arg, 0, j);
	if (arg[j] == '=')
	{
		value_len = ft_strlen(arg) - j - 1;
		value = ft_substr(arg, j + 1, value_len);
	}
	else
		value = NULL;
	export_to_env(&ctx->env, key, value);
	free(key);
	if (value)
		free(value);
}

void	print_export(t_env *env)
{
	t_env	*tmp = NULL;
	t_env	*copy = NULL;

	copy = copy_env(env);
	ft_sort_env_list(copy);
	tmp = copy;
	while (tmp)
	{
		if (tmp->key && ft_strcmp(tmp->key, "?") != 0 && ft_strcmp(tmp->key, "LINES") != 0 && ft_strcmp(tmp->key, "COLUMNS") != 0 && ft_strcmp(tmp->key, "_") != 0)
		{
			if (tmp->value == NULL)
				ft_fprintf(1, "declare -x %s\n", tmp->key);
			else
				ft_fprintf(1, "declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		}
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
		ft_memset(node, 0, sizeof(t_env));
		if (tmp->key)
			node->key = strdup(tmp->key);
		if (tmp->value)
			node->value = strdup(tmp->value);
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
