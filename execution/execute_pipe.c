/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:57:53 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/05 19:32:29 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
	* STDIN_FILENO = 0 = Entrée standard (clavier, pipe, <)
	* STDOUT_FILENO = 1 = Sortie standard (écran, pipe, >)
	* STDERR_FILENO = 2 = Sortie d'erreur standard (écran)
	* 
	* Waitpid remplie un status(int).
	* Les macros suivantes permettrent d'interprété ce status :
	* WIFEXITED (status) = Test si process c'est terminé normalement 
	* Return 1 (oui), 0 (non)
	* WEXITSTATUS(status) = récup le code de retour du fils
	* WIFSIGNALED(status) = return 1 si fils tué par un signal
	* WTERMSIG(status) = return num du signal
	*/

int	execute_pipeline(t_treenode *node, t_token *token, char *line)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	pid1 = fork();
	if (pid1 == -1)
		return (perror("fork1"), 1);
	if (pid1 == 0)
		pipe_left(node, token, line, pipefd);
	pid2 = fork();
	if (pid2 == -1)
		return (perror("fork2"), 1);
	if (pid2 == 0)
		pipe_right(node, token, line, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	return (pipe_status(node, pid1, pid2));
}

void	pipe_left(t_treenode *node, t_token *token, char *line, int pipefd[2])
{
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	exit(execute_node(node->left, token, line));
}

void	pipe_right(t_treenode *node, t_token *token, char *line, int pipefd[2])
{
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	exit(execute_node(node->right, token, line));
}

int	pipe_status(t_treenode *node, pid_t pid1, pid_t pid2)
{
	int	status1;
	int	status2;
	int	code_error;

	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFSIGNALED(status2))
		code_error = 128 + WTERMSIG(status2);
	else if (WIFEXITED(status2))
		code_error = 130 + WEXITSTATUS(status2);
	else
		code_error = 1;
	add_code_error(&node->env, code_error);
	return (code_error);
}
