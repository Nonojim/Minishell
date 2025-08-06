/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:53:57 by lduflot           #+#    #+#             */
/*   Updated: 2025/08/06 15:54:47 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_cd(t_treenode *node, t_ctx *ctx)
{
	char		*oldpwd;
	char		*target;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (ctx->exit_code = 1);
	if (node->argv[1] && node->argv[2])
		return (cd_many_arg(oldpwd, ctx));
	if (!node->argv[1] || ft_strcmp(node->argv[1], "-") == 0)
	{
		target = cd_home_oldpwd(node, oldpwd, ctx);
		if (!target)
			return (1);
	}
	else
		target = ft_strdup(node->argv[1]);
	if (cd_check_empty_target(target, node, oldpwd, ctx) == 1)
		return (1);
	if (cd_access(target, oldpwd, ctx) == 1)
		return (1);
	export_to_env(&ctx->env, "OLDPWD", oldpwd);
	free_cd(oldpwd, target);
	update_pwd(ctx);
	ctx->exit_code = 0;
	return (0);
}

/* Gestion de cd avec > 1 arg
ex: cd dir1 dir2*/
int	cd_many_arg(char *oldpwd, t_ctx *ctx)
{
	ft_fprintf(2, "minishell: cd: too many arguments\n");
	free_cd(oldpwd, NULL);
	ctx->exit_code = 1;
	return (1);
}

//Gestion de "cd"
char	*cd_home_target(char *oldpwd, t_ctx *ctx)
{
	char	*home;

	home = ft_getenv("HOME", ctx);
	if (!home || home[0] == '\0')
	{
		ft_fprintf(2, "minishell: cd: HOME not set\n");
		free_cd(oldpwd, NULL);
		ctx->exit_code = 1;
		return (NULL);
	}
	return (ft_strdup(home));
}

// Gestion de "cd-"
char	*cd_oldpwd_target(char *oldpwd, t_ctx *ctx)
{
	char	*old;

	old = ft_getenv("OLDPWD", ctx);
	if (!old || old[0] == '\0')
	{
		ft_fprintf(2, "minishell: cd: OLDPWD not set\n");
		free(oldpwd);
		ctx->exit_code = 1;
		return (NULL);
	}
	printf("%s\n", old);
	return (ft_strdup(old));
}

//Verifie cd dir
int	cd_check_empty_target(char *target, t_treenode *node,\
													char *oldpwd, t_ctx *ctx)
{
	if (!target || target[0] == '\0')
	{
		if (!node->argv[1])
			ft_fprintf(2, "minishell: cd: HOME not set\n");
		else
			ft_fprintf(2, "minishell: cd: %s: No such file or directory\n", \
node->argv[1]);
		free_cd(oldpwd, NULL);
		ctx->exit_code = 1;
		return (1);
	}
	return (0);
}
