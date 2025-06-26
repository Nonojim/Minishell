/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:28:25 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/26 07:42:03 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_export(t_env *env);

int	ft_export(t_treenode *node)
{
	int		i;
	int		j;
	int		value_len;
	char	*key;
	char	*value;
	

	i = 0;
	//si prompt = export
	if (node->argv[i + 1] == NULL)
	{
		print_export(node->env);
		return(0);
	}
	while(node->argv[i])
	{
		j = 0;
		while (node->argv[i][j] && node->argv[i][j] != '=')
			j++;
		if (node->argv[i][j] == '=')
		{
			key = ft_substr(node->argv[i], 0, j);
			value_len = ft_strlen(node->argv[i]) - j - 1;
			value = ft_substr(node->argv[i], j + 1, value_len);
			node->env = export_to_env(node->env, key, value);
			//printf("%s=%s\n", key, value);
			free(key);
			free(value);
		}
		i++;
	}
	return (0);
}

void	print_export(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while(tmp)
	{
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}


