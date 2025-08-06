/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command_external.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:58:47 by lduflot           #+#    #+#             */
/*   Updated: 2025/08/06 15:54:14 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_external_command(t_treenode *node, t_ctx *ctx, char *line)
{
	pid_t		pid;
	char		*cmd;

	if (!node->argv || !node->argv[0] || node->argv[0][0] == '#')
	{
		ctx->exit_code = 0;
		return (0);
	}
	if (node->argv[0][0] == '.' && node->argv[0][1] == '\0')
	{
		ft_fprintf(2, "minishell: .: filename argument required\n"
			".:usage: . filename [arguments]\n");
		return (2);
	}
	cmd = node->argv[0];
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		ctx->exit_code = 1;
		return (1);
	}
	if (pid == 0)
		handle_child_process(node, ctx, line, cmd);
	return (external_command_status(ctx, pid));
}

void	handle_child_process(t_treenode *node, t_ctx *ctx,\
														char *line, char *cmd)
{
	char	**array;
	char	*cmd_path;

	signal(SIGQUIT, SIG_DFL);
	cmd_path = shearch_cmd_path(cmd, ctx, line, node);
	if (access(cmd_path, F_OK) != 0)
	{
		ft_fprintf(2, "minishell: %s: No such file or directory\n", cmd_path);
		free_execve(ctx->root, line, ctx, cmd_path);
		exit(127);
	}
	if (access(cmd_path, X_OK) != 0)
	{
		ft_fprintf(2, "minishell: %s: Permission denied\n", cmd_path);
		free_execve(ctx->root, line, ctx, cmd_path);
		exit(126);
	}
	array = list_to_dynamiccarray(ctx);
	execve(cmd_path, node->argv, array);
	ft_fprintf(2, "minishell: %s: %s\n", cmd_path, strerror(errno));
	free_split(array);
	free_execve(ctx->root, line, ctx, cmd_path);
	if (errno == ENOENT)
		exit(127);
	exit(126);
}

char	*shearch_cmd_path(char *cmd, t_ctx *ctx, char *line, t_treenode *node)
{
	char		*cmd_path;
	struct stat	entry;

	if (!cmd || cmd[0] == '\0')
	{
		free_execve(node, line, ctx, NULL);
		exit(0);
	}
	if (cmd[0] == '.' || cmd[0] == '/')
		cmd_path = ft_strdup(cmd);
	else
		cmd_path = find_cmd_path(cmd, ctx->env);
	if (!cmd_path)
	{
		ft_fprintf(2, "minishell: %s: command not found\n", cmd);
		free_execve(ctx->root, line, ctx, NULL);
		exit(127);
	}
	if (stat(cmd_path, &entry) == 0 && S_ISDIR(entry.st_mode))
	{
		ft_fprintf(2, "minishell: %s: Is a directory\n", cmd_path);
		free_execve(ctx->root, line, ctx, cmd_path);
		exit(126);
	}
	return (cmd_path);
}

int	external_command_status(t_ctx *ctx, pid_t pid)
{
	int	status;
	int	sig;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			ft_fprintf(2, "Quit (core dumped)\n");
		else
			ft_fprintf(2, "\n");
		ctx->exit_code = 128 + WTERMSIG(status);
	}
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
