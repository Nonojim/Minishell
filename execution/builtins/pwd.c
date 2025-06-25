/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:04:30 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/25 22:20:16 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(t_treenode *node)
{
	char	*pwd;
	(void)node;
	/*if (ft_strcmp(node->argv[0], "pwd") != 0)
	{
		printf("%s: command not found\n", node->argv[0]);
		return (NULL);
	}
	else
	{*/
		pwd = ft_getenv("PWD", node);
		printf("%s\n", pwd);
	//}
	return (0);
}
