/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:25:50 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/25 10:26:02 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
Add command exit for quit programm properly during the test ./minishell
*/
void	ft_exit(char *line, t_token *token, t_treenode *ast)
{
	if (ft_strcmp(ast->argv[0], "exit") == 0)
	{
		free_treenode(ast);
		free_token(token);
		free(line);
		rl_clear_history();
		exit(0);
	}
}
