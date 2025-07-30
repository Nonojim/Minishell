/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:57:53 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/30 11:23:14 by lduflot          ###   ########.fr       */
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

int	execute_pipeline(t_treenode *node, char *line, t_ctx *ctx)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	pid1 = fork();
	if (pid1 == -1)
		return (perror("fork1"), 1);
	if (pid1 == 0)
		pipe_left(node, line, pipefd, ctx);
	pid2 = fork();
	if (pid2 == -1)
		return (perror("fork2"), 1);
	if (pid2 == 0)
		pipe_right(node, line, pipefd, ctx);
	close(pipefd[0]);
	close(pipefd[1]);
	signal(SIGINT, SIG_IGN);
	status = pipe_status(pid1, pid2, ctx);
	return (status);
}

void	pipe_left(t_treenode *node, char *line, int pipefd[2], t_ctx *ctx)
{
	int	exit_code;

	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	exit_code = execute_node(node->left, line, ctx);
	free_treenode(ctx->root);
	free_env_list(ctx->env);
	free(line);
	exit(exit_code);
}

void	pipe_right(t_treenode *node, char *line, int pipefd[2], t_ctx *ctx)
{
	int	exit_code;

	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	exit_code = execute_node(node->right, line, ctx);
	free_treenode(ctx->root);
	free_env_list(ctx->env);
	free(line);
	exit(exit_code);
}

int	pipe_status(pid_t pid1, pid_t pid2, t_ctx *ctx)
{
	int	status1;
	int	status2;

	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFSIGNALED(status2))
		ctx->exit_code = 128 + WTERMSIG(status2);
	else if (WIFEXITED(status2))
		ctx->exit_code = WEXITSTATUS(status2);
	else
		ctx->exit_code = 1;
	return (ctx->exit_code);
}
