/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_wildcard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:25:35 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/05 00:17:25 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*expand_wildcard(char *str);
int	match_prefix(char *str, char *prefix);
int	match_middle(char *str, char *middle);
int	match_suffix(char *str, char *suffix);
char	*add_string(char *result, char *file);
void	create_prefix_and_suffix(char **prefix, char **suffix, char *str);
char	*create_middle(char **middle, char *str);

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
*
*
*/
char	*expand_wildcard(char *str)
{
	DIR				*dir; //dossier ouvert = opendir
	struct dirent	*entry;
	char			*result;
	char			*prefix; //nom du fichier ex: on recherche les fichier ma*.c donc main.c
	char			*suffix; //terminaison du fichier ex: .c
	char			*middle; //*ai*

	result = ft_strdup("");
	dir = opendir("."); //ouverture du dossier courant "." = rep courant, ".." = dossier parent
	if (!dir || !str)
		return (ft_strdup(str)); 
	middle = NULL;
	printf("middle = %s\n", middle);
	create_prefix_and_suffix(&prefix, &suffix, str);
	middle = create_middle(&middle, str);	
	while ((entry = readdir(dir)) != NULL) //lecture des fichiers du rep courant
	{
		if (entry->d_name[0] == '.') //on ignore les files caché (ex .git)
			continue;
		if ((match_prefix(entry->d_name, prefix) && match_suffix(entry->d_name, suffix))) /*|| match_middle(entry->d_name, middle))*/ //ignore file caché 
			result = add_string(result, entry->d_name);
		else if(middle != NULL && match_middle(entry->d_name, middle))
			result = add_string(result, entry->d_name);
	}
	closedir(dir);
	free(prefix);
	free(suffix);
	if (result[0] == '\0')
	{
		free(result);
		str = ft_strdup(str);
		return (str);
	}
	return (result);
}

char	*create_middle(char **middle, char *str)
{
	int	end_middle = 0;
	int	i = 0;
	while(str[i] == '*')
		i++;
	int	start_middle = i;
	while(str[i] && str[i] != '*') // cas du *test*  ex: *ai* = main.c
		i++;
	end_middle = i;
	if (str[i] == '*')
	{
		while(str[i])
		{
			if (str[i] != '*')
				return (NULL);
			i++;
		}
		printf("middle after : %d\n", str[i]);
		printf("middle_in_fonction = %s\n", *middle);
		*middle = ft_substr(str, start_middle, end_middle-start_middle);
		return (*middle);
	}
	else 
		return (NULL);	
}

void	create_prefix_and_suffix(char **prefix, char **suffix, char *str)
{
	int	i;
	int	first_wildcard;

	i = 0;
	first_wildcard = 0;
	while (str[i] && str[i] != '*')
		i++;
	first_wildcard = i;
	while (str[i] && str[i] == '*') //on passe toutes les autres etoiles
		i++;
	*prefix = ft_substr(str, 0, first_wildcard);
	*suffix = ft_strdup(str + i); 
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
			{
				j++;
			}
		}
		i++;
		int	len_middle = ft_strlen(middle);
		if (j == len_middle)
			//return ((char *)&big[i - j]);
			return(0);
	}
	return (1);
}

int	match_middle(char *str, char *middle)
{
	int	match;
	int	len_str;

	if (!middle || middle[0] == '\0')
		return (1);
	len_str = ft_strlen(str);
	//char	*ft_strnstr(const char *big,	const char *little, size_t len)
	match = ft_strnstr_for_wildcard(str, middle, len_str);
	printf("match middle : %d\n", match);
	if (match == 0)
		return (1);
	return (0);
	//fonction qui cherche dans tous les files/folder de entry si il y a un ex:ai à l'intérieur
//trouver une fonction pour faire ça 
}

//verif que str comment par le prefix
int	match_prefix(char *str, char *prefix)
{
	int	match;
	int	len_prefix;
	
	if (!prefix || prefix[0] == '\0')
		return (1);
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

	if (!suffix || suffix[0] == '\0')
		return (1);
	len_str = ft_strlen(str);
	len_suffix = ft_strlen(suffix);
	match = ft_strcmp(str + len_str - len_suffix, suffix);
	if (match == 0)
		return (1);
	return (0);
}

//ajoute un space entre les resultats, return la string
char	*add_string(char *result, char *file)
{
	char	*tmp;
	char	*result2;

	tmp = ft_strjoin(result, file);
	result2 = ft_strjoin(tmp, " ");
	free(result);
	free(tmp);
	return (result2);
}
