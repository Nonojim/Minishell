/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:58:41 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/30 11:12:54 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int execute_subshell_node(t_treenode *node, t_token *token, char *line)
{
	pid_t pid = fork(); //on crée un nouveau process (enfant)
	int status; //stock code retour du process file
	int	code_error;

	if (pid == -1) //si fork échou (exemple de cause : trop de process lancé, manque de memory, restriction systeme)
	{
		perror("fork");
		code_error = 1;
	}
	else if (pid == 0)
		exit(execute_node(node->left, token, line)); // on exécute le sous-arbre récursivement
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
