/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:00:27 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/25 11:19:30 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
