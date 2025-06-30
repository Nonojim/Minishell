/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:58:21 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/30 13:01:29 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern char	**environ;
//Accede à une variable globale déclarée ailleur dans une lib, 
//celle-ci contiens toutes les variables d'env. 
//Même chose que faire : int maint(int argc, char **argv, char **envp).

int	execute_simple_command(t_treenode *node, t_token *token, char *line)
{
	int	code_error;

	if (!node || !node->str || !node->argv)
	{
		add_code_error(node->env, 1);
		return (1);
	}
	if (is_builtin(node->argv[0]))
		code_error = execute_builtin_command(node, token, line);
	else
		code_error = execute_external_command(node);
	node->env = add_code_error(node->env, code_error);
	return (code_error);
}
