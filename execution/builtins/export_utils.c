/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:46:41 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/23 12:47:58 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_export(t_env *env)
{
	t_env	*tmp;
	t_env	*copy;

	tmp = NULL;
	copy = NULL;
	copy = copy_env(env);
	ft_sort_env_list(copy);
	tmp = copy;
	while (tmp)
	{
		if (tmp->key && ft_strcmp(tmp->key, "?") != 0
			&& ft_strcmp(tmp->key, "LINES") != 0
			&& ft_strcmp(tmp->key, "COLUMNS") != 0
			&& ft_strcmp(tmp->key, "_") != 0)
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

void	ft_sort_env_list(t_env *env)
{
	t_env	*tmp;
	t_env	*start;
	char	*key_tmp;
	char	*value_tmp;

	if (!env)
		return ;
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

void	ft_env_add_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
