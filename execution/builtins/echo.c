/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:55:08 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/22 14:57:53 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_echo(t_treenode *node, t_ctx *ctx)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (node->argv[i + 1] == NULL)
		return (ft_fprintf(1, "\n"), 0);
	i++;
	while (node->argv[i] && ft_echo_n(node->argv[i]) == 1)
	{
		n = 1;
		i++;
	}
	while (node->argv[i])
	{
		ft_fprintf(1, "%s", node->argv[i]);
		if (node->argv[i + 1])
			ft_fprintf(1, " ");
		i++;
	}
	if (n == 0)
		ft_fprintf(1, "\n");
	ctx->exit_code = 0;
	return (ctx->exit_code);
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
