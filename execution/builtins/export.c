/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:28:25 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/04 13:01:16 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_export(t_treenode *node)
{
	int		i;

	i = 0;
	if (node->argv[i + 1] == NULL)
	{
		print_export(node->env);
		return (0);
	}
	while (node->argv[i])
	{
		add_export_variable(node, node->argv[i]);
		i++;
	}
	return (0);
}

void	add_export_variable(t_treenode *node, char *arg)
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
		node->env = export_to_env(node->env, key, value);
		free(key);
		free(value);
	}
}

void	print_export(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
