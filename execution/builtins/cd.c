/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:53:57 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/11 16:56:46 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_cd(t_treenode *node, t_ctx *ctx)
{
	char		*oldpwd;
	char		*newpwd;
	char		*target;
	struct stat	info;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (ctx->exit_code = 1);
	if (!node->argv[1])
		target = ft_getenv("HOME", ctx);
	if (!node->argv[1])
	{
		char *home = ft_getenv("HOME", ctx);
		if (!home || home[0] == '\0')
		{
			fprintf(stderr, "minishell: cd: HOME not set\n");
			free(oldpwd);
			return (ctx->exit_code = 1);
		}
		target = ft_strdup(home);
	}	
	else if (ft_strcmp(node->argv[1], "-") == 0)
	{
		char *old = ft_getenv("OLDPWD", ctx);
		if (!old || old[0] == '\0')
		{
			fprintf(stderr, "minishell: cd: OLDPWD not set\n");
			free(oldpwd);
			return (ctx->exit_code = 1);
		}
		target = ft_strdup(old);
		printf("%s\n", target);
	}
	else
		target = ft_strdup(node->argv[1]);
	if (!target || target[0] == '\0')
	{
		if (!node->argv[1])
			fprintf(stderr, "minishell: cd: HOME not set\n");
		else
			fprintf(stderr, "minishell: cd: %s: No such file or directory\n", node->argv[1]);
		free(oldpwd);
		free(target);
		return (ctx->exit_code = 1);
	}
	if (stat(target, &info) != 0)
	{
		fprintf(stderr, "minishell: cd: %s: No such file or directory\n", target);
		free(oldpwd);
		free(target);
		return (ctx->exit_code = 1);
	}
	if (!S_ISDIR(info.st_mode))
	{
		fprintf(stderr, "minishell: cd: %s: Not a directory\n", target);
		free(oldpwd);
		free(target);
		return (ctx->exit_code = 1);
	}
	if (chdir(target) != 0)
	{
		fprintf(stderr, "minishell: cd: %s: Permission denied\n", target);
		free(oldpwd);
		free(target);
		return (ctx->exit_code = 1);
	}
	export_to_env(&ctx->env, "OLDPWD", oldpwd);
	free(oldpwd);
	free(target);
	newpwd = getcwd(NULL, 0);
	if (newpwd)
	{
		export_to_env(&ctx->env, "PWD", newpwd);
		free(newpwd);
	}
	return (ctx->exit_code = 0);
}
