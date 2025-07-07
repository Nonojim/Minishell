/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:53:57 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/07 15:24:59 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*getcwd 	char *getcwd(char *buf, size_t size); 	Récupère le chemin absolu du répertoire courant

chdir 	int chdir(const char *path); 	Change le répertoire de travail courant.

stat 	int stat(const char *pathname, struct stat *statbuf); 	Récupère des informations sur un fichier ou un dossier.

closedir 	int closedir(DIR *dirp); 	Ferme un répertoire ouvert.*/

int	ft_cd(t_treenode *node, t_ctx *ctx)
{
	char		*oldpwd;
	char		*newpwd;
	char		*target;
	struct stat	info;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (add_code_error(&ctx->env, 1), 1);
	if (!node->argv[1])
		target = ft_getenv("HOME", ctx);
	else if (ft_strcmp(node->argv[1], "-") == 0)
	{
		target = ft_getenv("OLDPWD", ctx);
		if (!target || target[0] == '\0')
		{
			printf("cd: OLDPWD not set\n");
			free(oldpwd);
			free(target);
			return (add_code_error(&ctx->env, 1), 1);
		}
		printf("%s\n", target);
	}
	else
		target = ft_strdup(node->argv[1]);
	if (!target || target[0] == '\0')
	{
		if (!node->argv[1])
			printf("cd: HOME not set\n");
		else
			printf("cd: %s: No such file or directory\n", node->argv[1]);
		free(oldpwd);
		free(target);
		return (add_code_error(&ctx->env, 1), 1);
	}
	if (stat(target, &info) != 0)
	{
		printf("cd: %s: No such file or directory\n", target);
		free(oldpwd);
		free(target);
		return (add_code_error(&ctx->env, 1), 1);
	}
	if (!S_ISDIR(info.st_mode))
	{
		printf("cd: %s: Not a directory\n", target);
		free(oldpwd);
		free(target);
		return (add_code_error(&ctx->env, 1), 1);
	}
	if (chdir(target) != 0)
	{
		printf("cd: %s: Permission denied\n", target);
		free(oldpwd);
		free(target);
		return (add_code_error(&ctx->env, 1), 1);
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
	return (add_code_error(&ctx->env, 0), 0);
}

