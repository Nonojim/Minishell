/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:58:41 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/25 10:58:56 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int execute_subshell_node(t_treenode *node)
{
	pid_t pid = fork();
	int status;

	if (pid == 0)
		exit(execute_node(node->left)); // on exécute le sous-arbre
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
