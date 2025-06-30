/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:55:08 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/30 11:58:07 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_echo(t_treenode *node)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (node->argv[i + 1] == NULL)
	{
		printf("\n");
		return (0);
	}
	i++;
	while (node->argv[i] && ft_echo_n(node->argv[i]) == 1)
	{
		n = 1;
		i++;
	}
	while (node->argv[i])
	{
		printf("%s", node->argv[i]);
		printf(" ");
		i++;
	}
	if (n == 0)
		printf("\n");
	return (0);
}

//If there are "-nnnnnnnnnnnnnnnnnnnnnnnnnnn or -n -n -n"
int	ft_echo_n(char	*argv)
{
	int	i;

	i = 1;
	if (argv[0] != '-' || argv[1] != 'n')
		return (0);
	while (argv[i])
	{
		if (argv[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
