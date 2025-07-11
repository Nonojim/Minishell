/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fish.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:50:51 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/11 13:15:27 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"


int	ft_fish(t_treenode *node)
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
