/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:23:42 by npederen          #+#    #+#             */
/*   Updated: 2025/05/07 17:39:40 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Readline leak ==296785==    still reachable: 214,430 bytes in 259 blocks
int	main(void)
{
	char	*line;
	int		start;
	int		i;
	t_token	*token;

	while (1)
	{
		token = NULL;
		i = 0;
		start = 0;
		line = readline("Minishell$ ");
		if (line == NULL)
			break ;
		while (line[i] != '\0')
		{
			while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'
					|| line[i] == '\n'))
				i++;
			start = i;
			if ((line[i] == '\'' || line[i] == '\"') && line[i])
			{
				if (token_quote(&i, start, line, &token) == 1)
					continue ;
			}
			else if (is_operator_logical(line[i]) == line[i] && line[i])
				token_logical_operator(&i, start, line, &token);
			else if (line[i] != '\0' && is_word(line[i]) == 1)
				token_word(&i, start, line, &token);
		}	
		add_history(line);
		printf("i = %d\n", i);
		print_token_list(token);
		free_token(token);
		free(line);
	}
	return (0);
}
