/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:23:42 by npederen          #+#    #+#             */
/*   Updated: 2025/05/21 19:58:05 by npederen         ###   ########.fr       */
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
		t_treenode *tree = create_tree(token);
		astreeprint(tree, 0);
		//parse_simple_command_without_redirection(&token, NULL, 1);
		free_token(token);
		free(line);
	}
	rl_clear_history();
	return (0);
}
