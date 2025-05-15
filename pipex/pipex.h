/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:18:22 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/15 16:27:57 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../minishell.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>

# include <assert.h>


//Structure provisoire en attendant de le relier à l'AST
typedef struct s_pipe
{
	char **argv;
	struct s_pipe *next;
}			t_pipe;

/* urlographie
https://www.geeksforgeeks.org/fork-system-call/
https://www.delftstack.com/fr/howto/c/fork-in-c/
*/

/*
 * Access =        int access(const char *pathname, int mode);
 Verifie les droit d'accés a un fichier (ou dossier) sans l'ouvrir.
pathname = chemin vers fichier ou repertoire
mode = les droits que l'on veut vérifier. (possibilité de combiner plusieurs flag avec des pipe) e
mode = R_OK (read) W_OK (write) X_OK (exe) F_OK (savoir si le fichier existe)
Return = 0 (si autorisé), -1 si fichier inexistant
 
 * DUP = int dup(int oldfd); = crée un nouveau descripteur vers le même fichier 
  DUP2 = int dup2(int oldfd, int newfd); fais pointer newfs vers oldfd en remplacant ce qu'il t avait dans newfd
	Fonctioons pour manipuler les descripteurs de fichier. (nottament dans le cadre des redirection). 
	DUP et DUP2 = duplique un fd. 
créent une copie du descripteur de fichier oldfd. dup utilise le plus petit numéro inutilisé pour le nouveau descripteur. Dup2 transforme newfs en une copie de olffd fermantn auparavant newfd. 
	* EXECVE	int execve(const char *file, char *const argv[], char *const envp[]);
= execute le programme correspondant au fichier. 

	* FORK	pid_t fork(void);
	crée un nouveau processus en dupliquant le processus appelant. New processus = processus fils (copie exacte de l'appelant (du papa)).
Différence :
- Propre PID
- PPID (parent process ID) == PID parent
- 
	* PIPE	int pipe(int pipefd[2]);
crée un pipe, canal unidirectionnel de données pouvant être utilisé entre processus. 
Tableau pipefd = renvoie deux fd de fichiers = extrimité tube/pipe. pipefd[0] = lecture du tube pipefd[1] = écriture du tube 
Erreur = EFAULT = pipefd invalide, EMFILE = trop de fd use par le processus ENFILE = limite du nbr total de fichier ouvert sur le syt a été atteinte 
	* UNLINK	int unlink(const char *pathname);
	Supp un fichier du systeme de fichiers. (comme la commande rm dans shell)
	pathname = chemin du fichier a supp !! unlink ne supp pas directement le contenue du fichier mais supp le nom qui pointe vers lui dans le systeme de fichier. Unlink ne supprime ques les fichier (pour les dossiers il faudrait utiliser remove) !
	* WAIT	pid_t_wait(int *status)
	* WAITPID	pid_t_waitpid(pid_t pid, int *status, int options);
	 = Attendre la fin d'un processus enfant
	 permet de savoir quand l'enfant a terminé, récupérer son code de sortie, eviter que le processus enfant devienne un zombie (processus mort mais non nettoyé)
	 Macro pour analyser les status = WIFEXITED(status) = terminé normalement WEXITSTATUS(status) = code de retour SIFSIGNALED(status) = enfant tué par un signal WTERMSIG(status) = numéro du signal reçu 
	 wait = attend n'importe quel enfant terminé
	 waitpid = attend un enfant précis ou ne pas bloquer
 */

/*
 *
** Fonctions autorisés :
ft_printf, libft
open, close, read, write,
malloc, free, perror,
strerror, access, dup, dup2,
execve, exit, fork, pipe,
unlink, wait, waitpid

** Programme exucété comme suit:
./pipex file1 cmd1 cmd2 file2

** Arguments (4) 
file1 et file2 = nom de fichiers
cmd1 et cmd2 = commande shell avec leurs paramètres

**Shell d'exemple =
< file1 cmd1 | cmd2 > file2

**Exemple 
$> ./pipex infile "ls -l" "wc -l" outfile
Devrait être identique à < infile ls -l | wc -l > outfile
$> ./pipex infile "grep a1" "wc -w" outfile
Devrait être identique à < infile grep a1 | wc -w > outfile

**Bonus
Gérez plusieurs pipes.
Ceci :
$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
Devrait être identique à :
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
• Gérez « et » quand le premier paramètre est "here_doc".
Ceci :
$> ./pipex here_doc LIMITER cmd cmd1 file
Devrait être identique à :
cmd << LIMITER | cmd1 >> file
*
*/


# endif
