/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:55:08 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/25 12:22:29 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_echo(t_treenode *node)
{
	int	i;
	int	n;

	i = 0;
	//if (ft_strcmp(node->argv[0], "echo") != 0)
		//printf("%s: command not found\n", node->argv[0]);
	if (node->argv[i + 1] == NULL)
	{
		printf("\n");
		return (0);
	}
	n = ft_echo_n(node);
	if (n == 1)
		i += 2;
	else
		i = 1;
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

//If there are "-nnnnnnnnnnnnnnnnnnnnnnnnnnn"
int	ft_echo_n(t_treenode *node)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (node->argv[i][j] != '-')
		return (0);
	j++;
	while (node->argv[i][j])
	{
		if (node->argv[i][j] != 'n')
			return (0);
		j++;
	}
	i++;
	return (1);
}
