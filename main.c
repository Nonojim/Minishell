/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:23:42 by npederen          #+#    #+#             */
/*   Updated: 2025/07/10 18:25:32 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	char		*line;
	t_token		*token;
	t_token		*tmp;
	t_treenode	*ast;
	t_ctx		ctx;
	
	ctx.env = NULL;
	ctx.exit_code = 0;
	ctx.env = init_env_list();
	//int i = 0;
	//char **array = list_to_dynamiccarray(&ctx);
	//while (array[i])
	//{
	//	printf("%s\n", array[i]);
	//	i++;
	//}
	while (1)
	{
		setup_signals();
		token = NULL;
		line = readline("Minishell$ ");
		if (line == NULL)
			break ;
		token = tokenize(token, &line, &ctx);
		print_token_list(token);
		tmp = token;
		add_history(line);
		parse_error(0);
		ast = parse_line_node(&token);
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
	//(void)tmp;
	if (ast)
		free_treenode(ast);
	if (line)
		free(line);
}
