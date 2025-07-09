/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:58:21 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/09 13:06:32 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern char	**environ;
//Accede à une variable globale déclarée ailleur dans une lib, 
//celle-ci contiens toutes les variables d'env. 
//Même chose que faire : int maint(int argc, char **argv, char **envp).

int	execute_simple_command(t_treenode *node, t_token *token, char *line, t_ctx *ctx)
{
	if (!node || !node->str || !node->argv)
		return (ctx->exit_code = 1);
	expanse_ast(node, ctx);
	if (is_builtin(node->argv[0]))
		ctx->exit_code = execute_builtin_command(node, token, line, ctx);
	else
	{
		//free_token(token);
		ctx->exit_code = execute_external_command(node, ctx);
	}
	return (ctx->exit_code);
}
