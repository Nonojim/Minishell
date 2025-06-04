/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:23:42 by npederen          #+#    #+#             */
/*   Updated: 2025/06/04 17:01:27 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	* Add command exit for quit programm properly during the test ./minishell
*/
void	command_exit_for_testing(char *line, t_token *token)
{
	int	size_line;

	size_line = ft_strlen(line) + 1;
	if (line && ft_strncmp(line, "exit", size_line) == 0)
	{
		free_token(token);
		free(line);
		rl_clear_history();
		exit(0);
	}
}

//Readline leak ==296785==    still reachable: 214,430 bytes in 259 blocks
int	main(void)
{
	char	*line;
	t_token	*token;

	while (1)
	{
		token = NULL;
		line = readline("Minishell$ ");
		if (line == NULL)
			break ;
		command_exit_for_testing(line, token);
		token = tokenize(token, &line);
		add_history(line);
		print_token_list(token);
		t_treenode *tree = parse_line_node(&token);
		astreeprint(tree, 0);
	//	free_treenode(tree);
		free_token(token);
		free(line);
	}
	rl_clear_history();
	return (0);
}
