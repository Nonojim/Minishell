/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:33:54 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/24 16:37:12 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	**list_to_dynamiccarray(t_ctx *ctx)
{
	int		i;
	char	**array;
	t_env	*tmp;
	char	*key_eq;

	i = count_env(ctx->env);
	array = malloc(sizeof(char *) * (i + 1));
	if (!array)
		return (NULL);
	tmp = ctx->env;
	i = 0;
	while (tmp)
	{
		key_eq = ft_strdup(tmp->key);
		if (tmp->value)
			add_value(tmp, key_eq, array, &i);
		else
			array[i] = key_eq;
		i++;
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}

int	count_env(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

void	add_value(t_env *tmp, char *key_eq, char **array, int *i)
{
	free(key_eq);
	key_eq = ft_strjoin(tmp->key, "=");
	array[*i] = ft_strjoin(key_eq, tmp->value);
	free(key_eq);
}

void	free_execve(t_treenode *node, char *line, t_ctx *ctx, char *cmd_path)
{
	if (node)
		free_treenode(node);
	if (line)
		free(line);
	if (ctx)
		free_env_list(ctx->env);
	if (cmd_path)
		free(cmd_path);
}

void	free_split(char	**split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
