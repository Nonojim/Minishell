/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:58:00 by lduflot           #+#    #+#             */
/*   Updated: 2025/08/02 12:54:45 by npederen         ###   ########.fr       */
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
	char	cwd[1024];

	write(STDOUT_FILENO, "\033[2J\033[H", 7);
	usleep(200000);
	ft_fprintf(1, "\033[1;34m");
	ft_fprintf(1, "╭───────────────────────────────────────────╮\n");
	usleep(200000);
	ft_fprintf(1, "│      🐚 Welcome to Minishell — enjoy!     │\n");
	usleep(200000);
	ft_fprintf(1, "╰───────────────────────────────────────────╯\n");
	usleep(200000);
	ft_fprintf(1, "	\033[3;90m~ by Nonojim and Zephyre-ls ~\033[0;1;34m \n");
	usleep(200000);
	ft_fprintf(1, "\n");
	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_fprintf(1, "\033[1;34m🧭 You are here → %s\033[0m\n", cwd);
		usleep(200000);
	}
	ft_fprintf(1, "\n");
}

void	free_prompt(t_treenode *ast, char *line)
{
	if (ast)
		free_treenode(ast);
	if (line)
		free_then_setnull((void **)&line);

}

t_ctx	init_ctx(void)
{
	t_ctx	ctx;

	ft_memset(&ctx, 0, sizeof(t_ctx));
	ctx.env = init_env_list();
	return (ctx);
}
void	free_then_setnull(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}