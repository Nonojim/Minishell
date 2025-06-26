/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:23:42 by npederen          #+#    #+#             */
/*   Updated: 2025/06/26 11:44:06 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Readline leak ==296785==    still reachable: 214,430 bytes in 259 blocks
int	main(void)
{
	char		*line;
	t_token		*token;
	t_token		*tmp;
	t_treenode	*ast;
	t_env	*env_list;

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
		//print_token_list(token);
		parse_error(0); //remise à zéro de la static int error;
		ast = parse_line_node(&token);
		//si des tokens subsistent l'ast sera delete
		if (token != NULL)
		{
			print_error(token);
			free_treenode(ast);
			ast = NULL;
		}
		if (ast != NULL)
		{
			ast->env = env_list;
			expanse_ast(ast);
		//	astreeprint(ast, 0);
			execute_tree(ast);
			env_list = ast->env;
		}
		free_treenode(ast);
		free_token(tmp);
		free(line);
	}
	free_env_list(env_list);
	rl_clear_history();
	return (0);
}
