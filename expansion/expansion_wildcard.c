/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_wildcard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:25:35 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/08 15:43:51 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*expand_wildcard(char *str, t_treenode *node);
int	match_prefix(char *str, char *prefix);
int	match_middle(char *str, char *middle);
int	match_suffix(char *str, char *suffix);
char	**add_array(char **result, char *file);
void	create_prefix_middle_suffix(char *str, t_wildcard *psm);

char	*expand_wildcard(char *str, t_treenode *node)
{
	DIR				*dir; //dossier ouvert = opendir
	struct dirent	*entry;
	char			**result;
	t_wildcard *psm = malloc(sizeof(t_wildcard));

	if (!psm)
    return (NULL);
	psm->prefix = NULL;
	psm->middle = NULL;
	psm->suffix = NULL;
	dir = opendir("."); //ouverture du dossier courant "." = rep courant, ".." = dossier parent
	if (!dir)
		return (str);
	result = NULL;
	create_prefix_middle_suffix(str, psm);
	//printf("prefix : %s , middle: %s, suffix : %s \n", psm->prefix, psm->middle, psm->suffix);
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
		free(psm->middle);
		free(psm->prefix);
		free(psm->suffix);
		free(psm);
		return (NULL);
	}
	//pour conserver les autres argv 
	int	wildcard_index = 0;
	while (node->argv[wildcard_index] && ft_strchr(node->argv[wildcard_index], '*') == NULL)
		wildcard_index++;
	int len_argv = 0;
	while (node->argv[len_argv])
		len_argv++;
	int len_result = 0;
	while (result[len_result])
		len_result++;
	char **new_argv = malloc(sizeof(char *) * (len_argv + len_result));
	if (!new_argv)
		return (NULL);
	int i = 0;
	while (i < wildcard_index)
	{
		new_argv[i] = ft_strdup(node->argv[i]);
		i++;
	}
	//
	//creation des new_arg
	int j = 0;
	while (result[j])
	{
		new_argv[i + j] = result[j];
		j++;
	}
	int k = wildcard_index + 1;
	while (k < len_argv)
	{
		new_argv[i + j] = ft_strdup(node->argv[k]);
		k++;
		j++;
	}
	new_argv[i + j] = NULL;

	free_split(node->argv);
	free(result);
	free(psm->middle);
	free(psm->prefix);
	free(psm->suffix);
	free(psm);
	node->argv = new_argv;
	return (NULL);
}

void	create_prefix_middle_suffix(char *str, t_wildcard *psm)
{
	int	i = 0;
	int	start;


	if (str[i] && str[i] != '*')
	{
		start = 0;
		while (str[i] && str[i] != '*')
			i++;
		if (i > 0)
			psm->prefix = ft_substr(str, start, i - start);
	}
	while (str[i] == '*')
		i++;
	start = i;
	while (str[i] && str[i] != '*')
		i++;
	if (str[i] == '*')
	{
		if (i > start)
			psm->middle = ft_substr(str, start, i - start);
		while (str[i] == '*')
			i++;
		if (str[i])
			psm->suffix = ft_strdup(str + i);
	}
	else
	{
		if (i > start)
			psm->suffix = ft_substr(str, start, i - start);
	}
}


int	ft_strnstr_for_wildcard(char *str,	char *middle, int len_str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && i < len_str)
	{
		if (str[i] == middle[j])
			j++;
		else
		{
			i -= (j - 1);
			j = 0;
			if (str[i] == middle[0])
				j++;
		}
		i++;
		int	len_middle = ft_strlen(middle);
		if (j == len_middle)
			return(0);
	}
	return (1);
}
int	match_middle(char *str, char *middle)
{
	int	match;
	int	len_str;

	len_str = ft_strlen(str);
	match = ft_strnstr_for_wildcard(str, middle, len_str);
	if (match == 0)
		return (1);
	return (0);
}

//verif que str comment par le prefix
int	match_prefix(char *str, char *prefix)
{
	int	match;
	int	len_prefix;
	
	len_prefix = ft_strlen(prefix);
	match = ft_strncmp(str, prefix, len_prefix);
	if (match == 0)
		return (1);
	return (0);
}


//verif que str finit par le suffix
int	match_suffix(char *str, char *suffix)
{
	int	len_str;
	int	len_suffix;
	int	match;

	len_str = ft_strlen(str);
	len_suffix = ft_strlen(suffix);
	match = ft_strcmp(str + len_str - len_suffix, suffix);
	if (match == 0)
		return (1);
	return (0);
}

char	**add_array(char **result, char *file)
{
	int		i = 0;
	char	**new;

	while (result && result[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (result && result[i])
	{
		new[i] = result[i];
		i++;
	}
	new[i] = ft_strdup(file);
	new[i + 1] = NULL;
	free(result);
	//printf("ajout : %s\n", file);
	return (new);
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
	char           d_name[256]; // nom du fichier/dossier _ utile pour wilcard };
* 
* closedir(dir) = a la fin de la lecture on ferme le dossier pour free les ressources
*h
*/
