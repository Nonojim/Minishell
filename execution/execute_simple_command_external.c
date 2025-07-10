/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command_external.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:58:47 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/10 18:25:22 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern char	**environ;

char **list_to_dynamiccarray(t_ctx *ctx)
{
	int	i = 0;
	char	**array;
	t_env *tmp = ctx->env;
	while (tmp)
	{
		i++;	
		tmp = tmp->next;
	}
	free(tmp);
	array = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (ctx->env)
	{
		array[i] = ft_strjoin(ctx->env->key, ctx->env->value);
		i++;
		ctx->env = ctx->env->next;
	}
	array[i] = NULL;
	return (array);
}

int    execute_external_command(t_treenode *node, t_ctx *ctx)
{
	pid_t	pid;
	char	*cmd_path;
	char	*cmd;

	cmd = node->argv[0];
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		ctx->exit_code = 1;
		return (1);
	}
	if (pid == 0)
	{
		if(cmd[0] == '\0')
		{
			free_treenode(node);
			free_env_list(ctx->env);
			exit(0);
		}
		if (cmd[0] == '.' || cmd[0] == '/')
			cmd_path = ft_strdup(cmd);
		else
			cmd_path = find_cmd_path(cmd, ctx->env);
		if (!cmd_path)
		{
			fprintf(stderr, "minishell: %s: command not found\n", cmd);
			free_treenode(node);
			free_env_list(ctx->env);
			exit(127);
		}
		if (access(cmd_path, F_OK) != 0)
		{
			fprintf(stderr, "minishell: %s: No such file or directory\n", cmd_path);
			free_treenode(node);
			free_env_list(ctx->env);
			free(cmd_path);
			exit(127);
		}
		if (access(cmd_path, X_OK) != 0)
		{
			fprintf(stderr, "minishell: %s: Permission denied\n", cmd_path);
			free_treenode(node);
			free_env_list(ctx->env);
			free(cmd_path);
			exit(126);
		}
		execve(cmd_path, node->argv, list_to_dynamiccarray(ctx));
		fprintf(stderr, "minishell: %s: %s\n", cmd_path, strerror(errno));
		free(cmd_path);
		if (errno == ENOENT)
			exit(127);
		exit(126);
	}
	else
		return (external_command_status(ctx, pid));
	ctx->exit_code = 1; //EXECUTE QUAND ?
	return (1);
}

int	external_command_status(t_ctx *ctx, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		ctx->exit_code = 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
		ctx->exit_code = WEXITSTATUS(status);
	else
		ctx->exit_code = 1;
	return (ctx->exit_code);
}

char	*find_cmd_path(char *cmd, t_env *env_list)
{
	t_env	*path_node;
	char	**paths;
	int		i;
	char	*tmp;
	char	*cmd_path;

	path_node = find_usrvar(env_list, "PATH");
	if (!path_node || !path_node->value)
		return (NULL);
	paths = ft_split(path_node->value, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) == 0)
			return (free_split(paths), cmd_path);
		free(cmd_path);
		i++;
	}
	return (free_split(paths), NULL);
}

void	free_split(char	**split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split[i]);
	free(split);
}
