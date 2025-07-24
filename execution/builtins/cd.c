/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:53:57 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/23 12:58:05 by lduflot          ###   ########.fr       */
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

int	ft_cd(t_treenode *node, t_ctx *ctx)
{
	char		*oldpwd;
	char		*newpwd;
	char		*target;
	char		*home;
	char		*old;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (ctx->exit_code = 1);
	if (!node->argv[1])
		target = ft_getenv("HOME", ctx);
	if (node->argv[1] && node->argv[2])
	{
		ft_fprintf(2, "minishell: cd: too many arguments\n");
		free_cd(oldpwd, NULL);
		return (ctx->exit_code = 1);
	}
	if (!node->argv[1])
	{
		home = ft_getenv("HOME", ctx);
		if (!home || home[0] == '\0')
		{
			ft_fprintf(2, "minishell: cd: HOME not set\n");
			free_cd(oldpwd, NULL);
			return (ctx->exit_code = 1);
		}
		target = ft_strdup(home);
	}
	else if (node->argv[1] && ft_strcmp(node->argv[1], "-") == 0)
	{
		old = ft_getenv("OLDPWD", ctx);
		if (!old || old[0] == '\0')
		{
			ft_fprintf(2, "minishell: cd: OLDPWD not set\n");
			free_cd(oldpwd, NULL);
			return (ctx->exit_code = 1);
		}
		target = ft_strdup(old);
		printf("%s\n", target);
	}
	else
		target = ft_strdup(node->argv[1]);
	if (cd_access(target, oldpwd, ctx) == 1)
		return(1);
	if (!target || target[0] == '\0')
	{
		if (!node->argv[1])
			ft_fprintf(2, "minishell: cd: HOME not set\n");
		else
			ft_fprintf(2, "minishell: cd: %s: No such file or directory\n", node->argv[1]);
		free_cd(oldpwd, target);
		return (ctx->exit_code = 1);
	}
	export_to_env(&ctx->env, "OLDPWD", oldpwd);
	free_cd(oldpwd, target);
	newpwd = getcwd(NULL, 0);
	if (newpwd)
	{
		export_to_env(&ctx->env, "PWD", newpwd);
		free(newpwd);
	}
	return (ctx->exit_code = 0);
}
