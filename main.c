/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:23:42 by npederen          #+#    #+#             */
/*   Updated: 2025/06/30 13:52:51 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*line;
	t_token		*token;
	t_token		*tmp;
	t_treenode	*ast;
	t_env		*env_list;

	env_list = init_env_list();
	env_list = add_code_error(env_list, 0);
	while (1)
	{
		token = NULL;
		line = readline("Minishell$ ");
		if (line == NULL)
			break ;
		token = tokenize(token, &line);
		tmp = token;
		add_history(line);
		parse_error(0);
		ast = parse_line_node(&token);
		token_not_empty(&token, &ast);
		ast_is_created(ast, tmp, line, &env_list);
		free_prompt(ast, line, tmp);
	}
	return (free_env_list(env_list), rl_clear_history(), 0);
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

void	ast_is_created(t_treenode *ast, t_token *token,
			char *line, t_env **env_list)
{
	if (!ast)
		return ;
	ast->env = *env_list;
	expanse_ast(ast);
	execute_tree(ast, token, line);
	*env_list = ast->env;
}

void	free_prompt(t_treenode *ast, char *line, t_token *tmp)
{
	free_treenode(ast);
	free_token(tmp);
	free(line);
}
