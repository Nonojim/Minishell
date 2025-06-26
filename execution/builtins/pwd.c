/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:04:30 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/26 11:53:41 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(t_treenode *node)
{
	char	*pwd;
	(void)node;

	pwd = ft_getenv("PWD", node);
	printf("%s\n", pwd);
	return (0);
}
