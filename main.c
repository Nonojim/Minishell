/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:23:42 by npederen          #+#    #+#             */
/*   Updated: 2025/05/03 18:52:08 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*rl;

	while (1)
	{
		rl = readline("Minishell$ ");
		printf("%s\n", rl);
		free(rl);
		if (rl == NULL)
			break ;
	}
	return (0);
}
