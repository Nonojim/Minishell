/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:28:25 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/25 22:31:24 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_export(t_env *env);

int	ft_export(t_treenode *node)
{
	int	i;

	i = 0;
	//si prompt = export
	if (node->argv[i + 1] == NULL)
	{
		print_export(node->env);
		return(0);
	}
	while(node->argv[i])
	{
		char	*egal = ft_strchr(node->argv[i], '=');
		if (egal)
		{
			//egal = '\0';
			int	key_len = egal - node->argv[i];
			char	*key = ft_substr(node->argv[i], 0, key_len);
			char	*value = ft_strdup(egal + 1);
			node->env = export_to_env(node->env, key, value);
			printf("%s=%s\n", key, value);
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


