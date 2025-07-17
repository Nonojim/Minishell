/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:04:30 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/16 20:13:08 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(t_ctx *ctx)
{
	char	*pwd;

	pwd = ft_getenv("PWD", ctx);
	if (!pwd)
	{
		perror("pwd");
		ctx->exit_code = 1;
		return (1);
	}
	ft_fprintf(1, "%s\n", pwd);
	return (0);
}
