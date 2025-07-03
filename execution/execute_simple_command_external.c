/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command_external.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:58:47 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/03 12:18:49 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern char	**environ;

int    execute_external_command(t_treenode *node)
{
    pid_t    pid;
    char    *cmd_path;
    char    *cmd;

    cmd = node->argv[0];
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        node->env = add_code_error(node->env, 1);
    }
    if (pid == 0)
    {
        if (node->argv[0][0] == '.' && node->argv[0][1] == '/')
        {
            if (ft_strcmp(cmd, "./minishell") == 0 && access(node->argv[0], F_OK) == 0 && access(node->argv[0], X_OK) == 0)
                cmd_path = ft_strdup(node->argv[0]);
            else
            {
                printf("minishell: %s: No such file or directory\n", node->argv[0]);
                exit(127);
            }
        }
        else
        {
            cmd_path = find_cmd_path(cmd, node->env);
            if (!cmd_path)
            {
                printf("%s: command not found\n", node->argv[0]);
                exit(127);
            }
        }
        execve(cmd_path, node->argv, environ);
        free(cmd_path);
        exit(126);
    }
    else if (pid > 0)
        return (external_command_status(node, pid));
    node->env = add_code_error(node->env, 1);
    return (1);
} 

int	external_command_status(t_treenode *node, pid_t pid)
{
	int	status;
	int	code_error;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		code_error = 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
		code_error = WEXITSTATUS(status);
	else
		code_error = 1;
	node->env = add_code_error(node->env, code_error);
	return (code_error);
}

char	*find_cmd_path(char *cmd, t_env *env_list)
{
	t_env	*path_node;
	char	**paths;
	int		i;
	char	*tmp;
	char	*cmd_path;

	path_node = find_node(env_list, "PATH");
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
