/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_wildcard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:52:17 by lduflot           #+#    #+#             */
/*   Updated: 2025/08/06 11:05:36 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

t_wildcard	*init_struct_psm(int wildcard_index)
{
	t_wildcard	*psm;

	psm = malloc(sizeof(t_wildcard));
	if (!psm)
		return (NULL);
	psm->prefix = NULL;
	psm->suffix = NULL;
	psm->wildcard_index = wildcard_index;
	psm->len_result = 0;
	psm->len_argv = 0;
	return (psm);
}

void	wildcard_redir(char **result, t_ctx *ctx, t_wildcard *psm, \
										t_treenode *node)
{
	(void)ctx;
	if (result[1] != NULL)
	{
		ctx->exit_code = 1;
		ft_fprintf(2, "minishell: %s: ambiguous redirect\n", \
node->right->argv[0]);
		free_split(result);
		free_wildcard(psm, NULL, NULL);
		free_then_setnull((void **)&node->right->str);
		return ;
	}
	free(node->right->str);
	node->right->str = ft_strdup(result[0]);
	free_split(result);
	free_wildcard(psm, NULL, NULL);
	return ;
}

char	*result_wildcard(char **result, t_treenode *node, t_ctx *ctx, \
												t_wildcard *psm)
{
	if (!result)
	{
		free_wildcard(psm, result, NULL);
		return (NULL);
	}
	if (is_redirection_without_here_doc(node->type))
	{
		wildcard_redir(result, ctx, psm, node);
		return (NULL);
	}
	else
	{
		sort_argv(result);
		create_new_argv(result, node, psm);
		ctx->exit_code = 0;
	}
	return (NULL);
}

char	**found_match(DIR *dir, t_wildcard *psm, char **result)
{
	struct dirent	*entry;

	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] == '.')
		{
			entry = readdir(dir);
			continue ;
		}
		if ((psm->prefix == NULL || match_prefix(entry->d_name, psm->prefix))
			&& (psm->middle == NULL || match_middle(entry->d_name, psm->middle))
			&& (psm->suffix == NULL
				|| match_suffix(entry->d_name, psm->suffix)))
			result = add_array(result, entry->d_name);
		entry = readdir(dir);
	}
	return (result);
}

char	*expand_wildcard(char *str, t_treenode *node, t_ctx *ctx, \
												int wildcard_index)
{
	DIR				*dir;
	char			**result;
	t_wildcard		*psm;

	psm = init_struct_psm(wildcard_index);
	if (!psm)
		return (str);
	dir = opendir(".");
	if (!dir)
		return (str);
	result = NULL;
	create_prefix_middle_suffix(str, psm);
	result = found_match(dir, psm, result);
	closedir(dir);
	return (result_wildcard(result, node, ctx, psm));
}

/* = Glob 
 * PREFIXE***SUFFIXE 
 * ou more = affichage fichier/dossier
 * *.c = affiche fichier terminant par .c
 * *c / *txt = marche aussi 
 * mai*.c = affiche fichier avec mai en préfixe et .c en suffixe donc main.c 
 * *test* = affichage ou il y a test dedans
 * ls * ⁼ affichage dossier et fichiers à l'intérieur 
 * ls ** = même chose sauf si l'ont active 
 * : shopt -s globstar (mais désactivité automatiquement)
 * ls .* = affiche les fichiers cachés 
 * echo * = affiche files 
 * cat * = affiche l'intérieur des fichiers 
 * si * est entre simple/double quote 
 * = on affiche litteralement avec echo ou on renvoie une erreur direct 
 * si pas de correspondance trouvé avec echo on renvoie la demande *.md 

 */
/*Fonctions utile :
getcwd 	char *getcwd(char *buf, size_t size); 	
Récupère le chemin absolu du répertoire courant
chdir 	int chdir(const char *path); 	Change le répertoire de travail courant.
stat 	int stat(const char *pathname, struct stat *statbuf);
Récupère des informations sur un fichier ou un dossier.
opendir 	DIR *opendir(const char *name); 	Ouvre un répertoire pour lecture
closedir 	int closedir(DIR *dirp); 	Ferme un répertoire ouvert.
*/

/*
* DIR *dir = représente le dossier ouvert, obtenu avec opendir
* Lecture de ce dossier avec readdir, 
* readdir envoir un pointeur dans structdirent
* structure qui représente l'entrée d'un dossier. 
* struct dirent {
	ino_t          d_ino;       // numéro d'inode (peu utile ici)
	off_t          d_off;       // offset (utilisé par l'OS)
	unsigned short d_reclen;    // longueur de cette entrée
	unsigned char  d_type;      // type (fichier, dossier, etc.)
	// type : DT_REG (fichier normal), DT_DIR(dossier))
	char        d_name[256]; // nom du fichier/dossier_utile pour wildcard };
* closedir(dir) = 
* a la fin de la lecture on ferme le dossier pour free les ressources
*/
