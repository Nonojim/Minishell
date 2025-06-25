/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:00:05 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/25 17:29:25 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//Si j'écris cat avant << EOF dit ne pas reconnaitre la command. Lorsqu'on fait cat dans le reste du temps cela fonctionne
int execute_heredoc_node(t_treenode *node)
{
	int	pipefd[2];
	pipe(pipefd);
printf("HEREDOC node type: %d\n", node->type);
	printf("LEFT node type: %d, str: %s\n", node->left->type, node->left->str);
	printf("RIGHT node type: %d, str: %s\n", node->right->type, node->right->str);

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

