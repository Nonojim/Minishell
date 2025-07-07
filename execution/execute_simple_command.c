/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:58:21 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/07 15:06:38 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern char	**environ;
//Accede à une variable globale déclarée ailleur dans une lib, 
//celle-ci contiens toutes les variables d'env. 
//Même chose que faire : int maint(int argc, char **argv, char **envp).

int	execute_simple_command(t_treenode *node, t_token *token, char *line, t_ctx *ctx)
{
	int	code_error;

	if (!node || !node->str || !node->argv)
	{
		add_code_error(&ctx->env, 1);
		return (1);
	}
	expanse_ast(node, ctx);
	if (is_builtin(node->argv[0]))
		code_error = execute_builtin_command(node, token, line, ctx);
	else
		code_error = execute_external_command(node, ctx);
	add_code_error(&ctx->env, code_error);
	return (code_error);
}
