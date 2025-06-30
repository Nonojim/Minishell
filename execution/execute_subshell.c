/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:58:41 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/30 12:37:34 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_subshell_node(t_treenode *node, t_token *token, char *line)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		node->env = add_code_error(node->env, 1);
	}
	else if (pid == 0)
		exit(execute_node(node->left, token, line));
	return (subshell_status(node, pid));
}

int	subshell_status(t_treenode *node, pid_t pid)
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
