/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:23:42 by npederen          #+#    #+#             */
/*   Updated: 2025/07/17 11:10:44 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
\033 = ASCII = ESC 
\033[2J = Efface contenu de l'ecran (2: tout l'écran)
\033[H = Replace curseur position ligne 1, collone 1
*/
void	clear_screen(void)
{
	write(STDOUT_FILENO, "\033[2J\033[H", 7);
}

/*void	start_message(void)
{
	ft_fprintf(1, " en travaux ... \n");
	ft_fprintf(1, "\n");
}*/

int	main(void)
{
	char		*line;
	t_token		*token;
	t_token		*tmp;
	t_treenode	*ast;
	t_ctx		ctx;
	
	clear_screen();
	//start_message();
	ctx.env = NULL;
	ctx.exit_code = 0;
	ctx.root = NULL;
	ctx.env = init_env_list();
	while (1)
	{
		setup_signals();
		token = NULL;
		line = readline("\001\033[1;34m\002Minishell$ \001\033[0m\002");
		if (line == NULL)
			break ;
		if (g_signum == 2)
		{
			ctx.exit_code = 130;
			if (line[0] == '\0')
			{
				g_signum = 0;
				free(line);
				continue;
			}
		}
		g_signum = 0;
		token = tokenize(token, &line, &ctx);
		//print_token_list(token);
		tmp = token;
		add_history(line);
		parse_error(0);
		ast = parse_line_node(&token);
		if (parse_error(-1))
			ctx.exit_code = 2;
		//astreeprint(ast, 0);
		ctx.root = ast;
		token_not_empty(&token, &ast);
		free_token(tmp);
		resolve_ast(ast, line, &ctx);
		free_prompt(ast, line);
	}
	free_env_list(ctx.env);
	rl_clear_history();
	return (0);
}

void	token_not_empty(t_token **token, t_treenode **ast)
{
	if (*token)
	{
		print_error(*token);
		free_treenode(*ast);
		*ast = NULL;
	}
}

void	resolve_ast(t_treenode *ast, 
			char *line,	t_ctx	*ctx)
{
	if (!ast)
		return ;
	execute_tree(ast, line, ctx);
}

void	free_prompt(t_treenode *ast, char *line)
{
	if (ast)
		free_treenode(ast);
	if (line)
		free(line);
}
