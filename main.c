/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:23:42 by npederen          #+#    #+#             */
/*   Updated: 2025/05/08 02:05:49 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		token = tokenize(token, &line);
		add_history(line);
		print_token_list(token);
		free_token(token);
		free(line);
		rl_clear_history());
	}
	return (0);
}
