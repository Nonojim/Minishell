/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:43:16 by npederen          #+#    #+#             */
/*   Updated: 2025/06/21 18:41:28 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "execution.h"

//try to combine all redirection
int execute_redirection_chain(t_treenode *node)
{
	int saved_stdin = dup(STDIN_FILENO);
	int saved_stdout = dup(STDOUT_FILENO);
	int status;

	if (!node)
		return (1);

	if (node->type == INPUT_REDIRECTION)
	{
		int fd = open(node->right->str, O_RDONLY);
		if (fd < 0)
			return (perror("open <"), 1);
		dup2(fd, STDIN_FILENO);
		close(fd);
		status = execute_redirection_chain(node->left);
	}
	else if (node->type == OUTPUT_REDIRECTION)
	{
		int fd = open(node->right->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (perror("open >"), 1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		status = execute_redirection_chain(node->left);
	}
	else if (node->type == APPEND_OUTPUT_REDIRECTION)
	{
		int fd = open(node->right->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (perror("open >>"), 1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		status = execute_redirection_chain(node->left);
	}
	else
		status = execute_node(node);
		// Point d'arrêt : on exécute la commande
	// Restaurer les entrées/sorties
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (status);
}

int execute_heredoc_node(t_treenode *node)
{
	int	pipefd[2];
	pipe(pipefd);

	// Injecter le contenu du here-doc dans le pipe
	write(pipefd[1], node->right->str, strlen(node->right->str));
	close(pipefd[1]);

	// Exécuter la commande à gauche avec pipefd[0] comme stdin
	int	pid = fork();
	if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		exit(execute_node(node->left));  // execve etc dans cette fonction
	}
	close(pipefd[0]);
	int status;
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

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

int execute_subshell_node(t_treenode *node)
{
	pid_t pid = fork();
	int status;

	if (pid == 0)
		exit(execute_node(node->left)); // on exécute le sous-arbre
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int execute_simple_command(t_treenode *node)
{
	if (!node || !node->str || !node->argv)
		return (1);
	
	pid_t pid = fork();
	if (pid == 0)
	{
		// Enfant : on exécute la commande
		execve(node->argv[0], node->argv, NULL);
		perror("execve");
		exit(1);
	}
	else if (pid > 0)
	{
		int status;
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return WEXITSTATUS(status);
		return 1;
	}
	else
	{
		perror("fork");
		return (1);
	}
}

int	execute_node(t_treenode *node)
{
	if (!node)
		return (1);
	if (node->type == WORD)
		return(execute_simple_command(node));
	else if (node->type == PIPE)
		return (execute_pipeline(node));
	else if (node->type == LOGICAL_AND)
	{
		if (execute_node(node->left) == 0)
			return (execute_node(node->right));
		return (1);
	}
	else if (node->type == LOGICAL_OR)
	{
		if  (execute_node(node->left) == 0)
			return (0);
		return (execute_node(node->right));
	}
	else if (node->type == SEMICOLON)
	{
		execute_node(node->left);
		return (execute_node(node->right));
	}
	else if (node->type == HERE_DOCUMENT)
		return (execute_heredoc_node(node));
	else if (node->type == INPUT_REDIRECTION || node->type == OUTPUT_REDIRECTION || node->type == APPEND_OUTPUT_REDIRECTION)
		return (execute_redirection_chain(node));
	else if (node->type == SUBSHELL)
		return (execute_subshell_node(node));
	else
	{
		printf("unknown node type %d", node->type);
		return(1);
	}
}

void	execute_tree(t_treenode *tree)
{
	execute_node(tree);
}

//REDIRECTION

//int execute_redirection_in_node(t_treenode *node)
//{
//	int fd = open(node->right->str, O_RDONLY);
//	if (fd < 0)
//		return perror("open <"), 1;
//
//	int saved_stdin = dup(STDIN_FILENO);
//	dup2(fd, STDIN_FILENO);
//	close(fd);
//
//	int status = execute_node(node->left);
//
//	dup2(saved_stdin, STDIN_FILENO);
//	close(saved_stdin);
//	return status;
//}
//
//int execute_redirection_out_node(t_treenode *node)
//{
//	int fd = open(node->right->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//	if (fd < 0)
//		return perror("open >"), 1;
//
//	int saved_stdout = dup(STDOUT_FILENO);
//	dup2(fd, STDOUT_FILENO);
//	close(fd);
//
//	int status = execute_node(node->left);
//
//	dup2(saved_stdout, STDOUT_FILENO);
//	close(saved_stdout);
//	return status;
//}
//
//int execute_redirection_append_node(t_treenode *node)
//{
//	int fd = open(node->right->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
//	if (fd < 0)
//		return perror("open >>"), 1;
//
//	int saved_stdout = dup(STDOUT_FILENO);
//	dup2(fd, STDOUT_FILENO);
//	close(fd);
//
//	int status = execute_node(node->left);
//
//	dup2(saved_stdout, STDOUT_FILENO);
//	close(saved_stdout);
//	return status;
//}