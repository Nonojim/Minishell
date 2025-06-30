/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:00:05 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/30 11:10:09 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//Si j'écris cat avant << EOF dit ne pas reconnaitre la command. Lorsqu'on fait cat dans le reste du temps cela fonctionne

int execute_heredoc_node(t_treenode *node, t_token *token, char *line)
{
	int	pipefd[2];
	pipe(pipefd);

	// Injecter le contenu du here-doc dans le pipe (écriture)
	write(pipefd[1], node->right->str, ft_strlen(node->right->str));
	close(pipefd[1]); //ferme write une fois donné send

	// Exécuter la commande à gauche avec pipefd[0] comme stdin, fork pour exe la commande qui va manger le here doc
	int	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		node->env = add_code_error(node->env, 1);
		return (1);
	}	
	if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		exit(execute_node(node->left, token, line));  // execve etc dans cette fonction
	}
	close(pipefd[0]);
	int status;
	int	code_error;
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		node->env = add_code_error(node->env, 1);
		return (1);
	}
	if (WIFSIGNALED(status))
		code_error = 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
		code_error = WEXITSTATUS(status);
	else
		code_error = 1;
	node->env = add_code_error(node->env, code_error);
	return (code_error);
}
