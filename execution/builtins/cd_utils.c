/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:06:08 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/24 13:24:25 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	free_cd(char *oldpwd, char *target)
{
	if (oldpwd)
		free(oldpwd);
	if (target)
		free(target);
}

//Verifie si le chemin est accessible
int	cd_access(char *target, char *oldpwd, t_ctx *ctx)
{
	struct stat	info;

	if (stat(target, &info) != 0)
	{
		ft_fprintf(2, "minishell: cd: %s: No such file or directory\n", target);
		free_cd(oldpwd, target);
		return (ctx->exit_code = 1);
	}
	if (!S_ISDIR(info.st_mode))
	{
		ft_fprintf(2, "minishell: cd: %s: Not a directory\n", target);
		free_cd(oldpwd, target);
		return (ctx->exit_code = 1);
	}
	if (chdir(target) != 0)
	{
		ft_fprintf(2, "minishell: cd: %s: Permission denied\n", target);
		free_cd(oldpwd, target);
		return (ctx->exit_code = 1);
	}
	return (0);
}

//met à jour pwd aprés un "cd"
void	update_pwd(t_ctx *ctx)
{
	char	*newpwd;

	newpwd = getcwd(NULL, 0);
	if (newpwd)
	{
		export_to_env(&ctx->env, "PWD", newpwd);
		free(newpwd);
	}
}
