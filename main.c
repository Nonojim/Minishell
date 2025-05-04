/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:23:42 by npederen          #+#    #+#             */
/*   Updated: 2025/05/04 15:57:34 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*rl;
	int	size_line;

	printf("%d , %d\n", BRACKETS_L, WORD);
	while (1)
	{
		rl = readline("Minishell$ ");
		if(rl)
			add_history(rl);
		printf("%s\n", rl);
		size_line = ft_strlen(rl);
		printf("taille prompt: %d\n", size_line);
		free(rl);
		if (rl == NULL)
			break;
	}
	return (0);
}
