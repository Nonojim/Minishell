/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:57:53 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/25 10:58:15 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int execute_pipeline(t_treenode *node)
{
	int pipefd[2];
	pid_t pid1, pid2;
	int status1, status2;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);

	pid1 = fork();
	if (pid1 == 0)
	{
		// Fils 1 : left side
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		exit(execute_node(node->left));
	}

	pid2 = fork();
	if (pid2 == 0)
	{
		// Fils 2 : right side
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		exit(execute_node(node->right));
	}

	// Parent
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	return (WEXITSTATUS(status2)); // On retourne le code du dernier
}
