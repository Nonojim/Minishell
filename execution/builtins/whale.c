/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:50:51 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/22 14:33:53 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_whale(t_treenode *node)
{
	(void)node;
	printf("       .\n");
	printf("      \":\"\n");
	printf("    ___:____     |\"\\/\"|\n");
	printf("  ,'        `.    \\  /\n");
	printf("  |  O        \\___/  |\n");
	printf("~^~^~^~^~^~^~^~^~^~^~^~^~\n");
	printf(" Oh Capitaine, you've discovered a whale in your Minishell!\n");
	return (0);
}
