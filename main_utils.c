/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:58:00 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/28 10:00:39 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
\033 = ASCII = ESC 
\033[2J = Efface contenu de l'ecran (2: tout l'écran)
\033[H = Replace curseur position ligne 1, collone 1
*/
void	start_message(void)
{
	write(STDOUT_FILENO, "\033[2J\033[H", 7);
	ft_fprintf(1, "\033[1;34m╔════════════════════════════════════════════╗\n");
	usleep(200000);
	ft_fprintf(1, "║                                            ║\n");
	usleep(200000);
	ft_fprintf(1, "║        Welcome to Minishell — enjoy!       ║\n");
	usleep(200000);
	ft_fprintf(1, "║                                            ║\n");
	usleep(200000);
	ft_fprintf(1, "╚════════════════════════════════════════════╝\033[0m\n");
	usleep(200000);
	ft_fprintf(1, "\033[3;90mby Nonojim and Zephyre-ls\033[0;34m   \n");
	usleep(200000);
	ft_fprintf(1, "\n");
}

void	free_prompt(t_treenode *ast, char *line)
{
	if (ast)
		free_treenode(ast);
	if (line)
		free(line);
}

t_ctx	init_ctx(void)
{
	t_ctx	ctx;

	ft_memset(&ctx, 0, sizeof(t_ctx));
	ctx.env = init_env_list();
	return (ctx);
}
