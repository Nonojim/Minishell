/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:53:57 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/30 11:04:20 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*getcwd 	char *getcwd(char *buf, size_t size); 	Récupère le chemin absolu du répertoire courant

chdir 	int chdir(const char *path); 	Change le répertoire de travail courant.

stat 	int stat(const char *pathname, struct stat *statbuf); 	Récupère des informations sur un fichier ou un dossier.

closedir 	int closedir(DIR *dirp); 	Ferme un répertoire ouvert.*/

int	ft_cd(t_treenode *node)
{
	char		*oldpwd;  // Stocke le répertoire courant avant le changement
	char		*newpwd;  // Stockera le nouveau répertoire après le changement
	char		*target;  // Cible du changement de dossier
	struct stat	info;     // Utilisé pour vérifier si la cible est un répertoire

	//Obtenir le répertoire courant actuel (allocation dynamique)
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		// Échec de getcwd → on met $?=1 et on quitte
		return (node->env = add_code_error(node->env, 1), 1);

	//Déterminer la destination vers laquelle on veut aller
	if (!node->argv[1])
		// Aucun argument → aller dans $HOME
		target = ft_getenv("HOME", node);
	else if (ft_strcmp(node->argv[1], "-") == 0)
	{
		// cd - → aller dans $OLDPWD (répertoire précédent)
		target = ft_getenv("OLDPWD", node);
		if (!target || target[0] == '\0')
		{
			// Si $OLDPWD n'est pas défini → erreur
			printf("cd: OLDPWD not set\n");
			free(oldpwd);
			free(target);
			return (node->env = add_code_error(node->env, 1), 1);
		}
		// Bash affiche le chemin lorsqu'on fait "cd -"
		printf("%s\n", target);
	}
	else
		// Sinon, l'argument donné est le chemin cible
		target = ft_strdup(node->argv[1]);

	// Si la cible est vide ou nulle → erreur
	if (!target || target[0] == '\0')
	{
		if (!node->argv[1])
			printf("cd: HOME not set\n");
		else
			printf("cd: %s: No such file or directory\n", node->argv[1]);
		free(oldpwd);
		free(target);
		return (node->env = add_code_error(node->env, 1), 1);
	}

	//Vérifie que la cible existe et est bien un répertoire
	if (stat(target, &info) != 0)
	{
		printf("cd: %s: No such file or directory\n", target);
		free(oldpwd);
		free(target);
		return (node->env = add_code_error(node->env, 1), 1);
	}
	if (!S_ISDIR(info.st_mode))
	{
		printf("cd: %s: Not a directory\n", target);
		free(oldpwd);
		free(target);
		return (node->env = add_code_error(node->env, 1), 1);
	}

	//Tente de changer de répertoire
	if (chdir(target) != 0)
	{
		printf("cd: %s: Permission denied\n", target);
		free(oldpwd);
		free(target);
		return (node->env = add_code_error(node->env, 1), 1);
	}

	//Mise à jour de OLDPWD avec l’ancien répertoire
	node->env = export_to_env(node->env, "OLDPWD", oldpwd);
	free(oldpwd);  // libère l'ancien chemin
	free(target);  // libère le chemin cible

	//Mise à jour de PWD avec le nouveau répertoire courant
	newpwd = getcwd(NULL, 0);
	if (newpwd)
	{
		node->env = export_to_env(node->env, "PWD", newpwd);
		free(newpwd);
	}

	//Succès → mise à jour de $? avec 0
	return (node->env = add_code_error(node->env, 0), 0);
}

