/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:23:42 by npederen          #+#    #+#             */
/*   Updated: 2025/07/13 10:34:20 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_ascii_printable(const char *str)
{
	int	i = 0;
	while(str[i])
	{
		if ((unsigned char)str[i] < 1 || (unsigned char)str[i] > 126)
			return (1);
		i++;
	}
	return (0);
}

int	main(void)
{
	char		*line;
	t_token		*token;
	t_token		*tmp;
	t_treenode	*ast;
	t_ctx		ctx;
	
	ctx.env = NULL;
	ctx.exit_code = 0;
	ctx.root = NULL;
	ctx.env = init_env_list();
	while (1)
	{
		setup_signals();
		token = NULL;
		line = readline("Minishell$ ");
		if (line == NULL)
			break ;
		if (g_signum == 1)
		{
			ctx.exit_code = 130;
			if (line[0] == '\0')
			{
				g_signum = 0;
				free(line);
				continue;
			}
		}
		//if (is_ascii_printable(line))
		//{
		//	fprintf(stderr, "minishell: unrecognized character\n");
		//	free(line);
		//	continue ;
		//}
		g_signum = 0;
		token = tokenize(token, &line, &ctx);
		//print_token_list(token);
		tmp = token;
		add_history(line);
		parse_error(0);
		ast = parse_line_node(&token);
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
