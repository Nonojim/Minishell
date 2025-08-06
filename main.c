/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:23:42 by npederen          #+#    #+#             */
/*   Updated: 2025/07/30 23:18:27 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_ctx		ctx;

	start_message();
	ctx = init_ctx();
	main_loop(&ctx);
	free_env_list(ctx.env);
	rl_clear_history();
	return (0);
}

void	main_loop(t_ctx *ctx)
{
	char		*line;
	t_token		*token;
	t_treenode	*ast;

	while (1)
	{
		token = NULL;
		setup_signals();
		line = readline("\001\033[1;34m\002Minishell$ \001\033[0m\002");
		if (line == NULL)
			break ;
		if (signal_interrupt(line, ctx) == 1)
			continue ;
		if (line && *line && is_printable_str(line))
			add_history(line);
		token = tokenize(token, &line, ctx);
		ctx->head_token_list = token;
		parse_error(0);
		ast = parse_line_node(&token);
		if (parse_error(-1))
			ctx->exit_code = 2;
		ctx->root = ast;
		token_not_empty(&token, &ast, ctx->head_token_list);
		resolve_ast(ast, line, ctx);
	}
}

int	signal_interrupt(char *line, t_ctx *ctx)
{
	if (g_signum == 2)
	{
		ctx->exit_code = 130;
		if (line[0] == '\0')
		{
			g_signum = 0;
			free(line);
			return (1);
		}
	}
	g_signum = 0;
	return (0);
}

void	token_not_empty(t_token **token, t_treenode **ast, t_token *tmp)
{
	if (*token)
	{
		print_error(*token);
		free_treenode(*ast);
		*ast = NULL;
	}
	free_token(tmp);
	tmp = NULL;
}

void	resolve_ast(t_treenode *ast, char *line, t_ctx *ctx)
{
	if (!ast)
	{
		if (line)
			free(line);
		return ;
	}
	execute_tree(ast, line, ctx);
	free_prompt(ast, line);
}
