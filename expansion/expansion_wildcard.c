/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_wildcard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:25:35 by lduflot           #+#    #+#             */
/* ************************************************************************** */

#include "expansion.h"
	
void	create_new_argv(char **result, t_treenode *node, t_wildcard *psm)
{
	int	wildcard_index;
	int	len_argv;
	int	len_result;
	char	**new_argv;
	int	i;
	int	j;
	int	k;

	if (!node || !node->argv)
		return ;
	wildcard_index = 0;
	while (node->argv[wildcard_index] && ft_strchr(node->argv[wildcard_index], '*') == NULL)
		wildcard_index++;
	len_argv = 0;
	while (node->argv[len_argv])
		len_argv++;
	len_result = 0;
	while (result[len_result])
		len_result++;
	new_argv = malloc(sizeof(char *) * (len_argv + len_result));
	if (!new_argv)
		return ;
	i = 0;
	while (i < wildcard_index)
	{
		new_argv[i] = ft_strdup(node->argv[i]);
		i++;
	}
	j = 0;
	while (result[j])
	{
		new_argv[i + j] = result[j];
		j++;
	}
	k = wildcard_index + 1;
	while (k < len_argv)
	{
		new_argv[i + j] = ft_strdup(node->argv[k]);
		k++;
		j++;
	}
	new_argv[i + j] = NULL;
	free_wildcard(psm, result, node);
	node->argv = new_argv;
}

char	*expand_wildcard(char *str, t_treenode *node)
{
	DIR				*dir; //dossier ouvert = opendir
	struct dirent	*entry;
	char			**result;
	t_wildcard *psm = malloc(sizeof(t_wildcard));

	if (!psm)
    return (NULL);
	psm->prefix = NULL;
	psm->suffix = NULL;
	dir = opendir("."); //ouverture du dossier courant "." = rep courant, ".." = dossier parent
	if (!dir)
		return (str);
	result = NULL;
	create_prefix_middle_suffix(str, psm);
	while ((entry = readdir(dir)) != NULL) //lecture des fichiers du rep courant
	{
		if (entry->d_name[0] == '.') //on ignore les files caché (ex .git)
			continue;
		if ((psm->prefix == NULL || match_prefix(entry->d_name, psm->prefix)) &&
				(psm->middle == NULL || match_middle(entry->d_name, psm->middle)) &&
				(psm->suffix == NULL || match_suffix(entry->d_name, psm->suffix)))
			result = add_array(result, entry->d_name);
	}
	closedir(dir);
	if (!result)
	{
		free_wildcard(psm, result, NULL);
		return (NULL);
	}
	if (node->type == INPUT_REDIRECTION
		|| node->type == OUTPUT_REDIRECTION
		|| node->type == APPEND_OUTPUT_REDIRECTION)
	{
		if (result [1] != NULL)
		{
		//	ctx->exit_code = 1; A DECLARER DANS LA FONCTION
			ft_fprintf(2, "minishell: ambiguous redirection\n");
			free_split(result);
			free_wildcard(psm, NULL, NULL);
			return (NULL);
		}
		free(node->right->str);
		node->right->str = ft_strdup(result[0]);
		free_split(result);
		free_wildcard(psm, NULL, NULL);
		return (NULL);
	}
	else
		create_new_argv(result, node, psm);
	return (NULL);
}

/* = Glob 
 * PREFIXE***SUFFIXE 
 * ou more = affichage fichier/dossier
 * *.c = affiche fichier terminant par .c
 * *c / *txt = marche aussi 
 * mai*.c = affiche fichier avec mai en préfixe et .c en suffixe donc main.c 
 * *test* = affichage ou il y a test dedans
 * ls * ⁼ affichage dossier et fichiers à l'intérieur 
 * ls ** = même chose sauf si l'ont active : shopt -s globstar (mais désactivité automatiquement)
 * ls .* = affiche les fichiers cachés 
 * echo * = affiche files 
 * cat * = affiche l'intérieur des fichiers 
 * si * est entre simple/double quote = on affiche litteralement avec echo ou on renvoie une erreur direct 
 * si pas de correspondance trouvé avec echo on renvoie la demande *.md 

 */
/*Fonctions utile :
getcwd 	char *getcwd(char *buf, size_t size); 	Récupère le chemin absolu du répertoire courant
chdir 	int chdir(const char *path); 	Change le répertoire de travail courant.
stat 	int stat(const char *pathname, struct stat *statbuf); 	Récupère des informations sur un fichier ou un dossier.
opendir 	DIR *opendir(const char *name); 	Ouvre un répertoire pour lecture
closedir 	int closedir(DIR *dirp); 	Ferme un répertoire ouvert.
*/

/*
* DIR *dir = représente le dossier ouvert, obtenu avec opendir
* Lecture de ce dossier avec readdir, readdir envoir un pointeur dans structdirent
*
* structure qui représente l'entrée d'un dossier. 
* struct dirent {
	ino_t          d_ino;       // numéro d'inode (peu utile ici)
	off_t          d_off;       // offset (utilisé par l'OS)
	unsigned short d_reclen;    // longueur de cette entrée
	unsigned char  d_type;      // type (fichier, dossier, etc.)
	// type : DT_REG (fichier normal), DT_DIR(dossier))
	char           d_name[256]; // nom du fichier/dossier _ utile pour wildcard };
* 
* closedir(dir) = a la fin de la lecture on ferme le dossier pour free les ressources
*h
*/
