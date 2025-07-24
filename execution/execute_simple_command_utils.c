/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:33:54 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/23 12:35:12 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	**list_to_dynamiccarray(t_ctx *ctx)
{
	int		i;
	char	**array;
	t_env	*tmp;
	char	*key_eq;

	i = 0;
	tmp = ctx->env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	array = malloc(sizeof(char *) * (i + 1));
	if (!array)
		return (NULL);
	tmp = ctx->env;
	i = 0;
	while (tmp)
	{
		key_eq = ft_strdup(tmp->key);
		if (tmp->value)
		{
			free(key_eq);
			key_eq = ft_strjoin(tmp->key, "=");
			array[i] = ft_strjoin(key_eq, tmp->value);
			free(key_eq);
		}
		else
			array[i] = key_eq;
		i++;
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
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
