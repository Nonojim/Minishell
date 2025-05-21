/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:27:50 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/18 09:01:07 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * Type de sorties :
stdin = entrée standart = ce que le programme lit int 0
stdout = sortie standart = ce que le programme affiche int 1
stderr = erreur standart = erreur envoyé par le programme int 2 
DONC si on fait ls -l | wc -l
ls -l est renvoyé sur le sdout du pipe, et wc -l à le stdin.
Les sorties sont une variable en c (FILE *stdout, *stdin, *stderr);
= pointeur vers des flux
_FILENO (à la fin des sorties), numéro de fichier
= descripteur de fichier
*/

int	create_pipe(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		printf("Error create pipe\n");
		exit (EXIT_FAILURE);
	}
	return (0);
}

/*
 * FORK = sert à dupliquer le processus courant. 
 * fork > 0 = processus pareil (processsus original)
 * fork == 0 = processus enfant
 * fork == -1 = erreur
 * Les processus sont independant mais peuvent communiquer via des pipes; ou partager des fichiers ouvert.
 * Exemple ls | wc -l 
          [ Processus parent ]
                |
     ┌──────────┴──────────┐
     |                     |
 [ fork() ]           [ fork() ]
     |                     |
 [ Enfant 1 ]         [ Enfant 2 ]
 (devient ls)         (devient wc -l)
     |                     |
 dup2(pipefd[1], 1)   dup2(pipefd[0], 0)
     |                     |
    stdout ───► pipe ───► stdin
Resultat = 
> ./a.out
ls produit :        "fichier1\nfichier2\n..."
→ passe dans pipe
wc lit :            "fichier1\nfichier2\n..."
→ compte les lignes
→ affiche :         "2"

 */
void	exec_pipeline(t_pipe *cmd)
{
	int	pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	create_pipe(pipefd);
	pid1 = fork();
	if (pid1 == -1)
	{
		printf("Error create fork\n");
		exit (EXIT_FAILURE);
	}
	if (pid1 == 0)
	{
		close(pipefd[0]); //le premier processus écrit dans le pipe et le ne lit donc close lecture
		dup2(pipefd[1], STDOUT_FILENO); // redirection stdout vers le pipe
		close(pipefd[1]);
		execvp(cmd->argv[0], cmd->argv);
		exit(EXIT_FAILURE);
	}
	pid2 = fork();
	if (pid2 == -1)
	{
		printf("Error create fork\n");
		exit (EXIT_FAILURE);
	}
	if (pid2 == 0)
	{
		close(pipefd[1]); //le 2nd processus lit mais n'écrit pas, donc fermeture ecriture
		dup2(pipefd[0], STDIN_FILENO); // redirection stdin vers le pipe
		close(pipefd[0]);
		execvp(cmd->argv[0], cmd->argv);
		exit(EXIT_FAILURE);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int argc, char **argv)
{
	t_pipe cmd;
	t_pipe cmd2;

	(void)argc;

	cmd.argv = ft_split(argv[1], ' ');
	cmd.next = &cmd2;
	cmd2.argv = ft_split(argv[2], ' ');
	cmd2.next = NULL;
	exec_pipeline(&cmd);
	//exec_pipeline(&cmd2);
	return (0);
}

//Exemple du man pipe :
// Creation d'un pipe.
// Le processus parents écrit "argv" dans le pipe
// Le processus enfant lit ce que le parent a écrit et l'affiche caractere par caractere sur la sortie standart (stdout).
/*int	main(int argc, char **argv)
{
	int pipefd[2]; //Tableau qui stocke les 2 extrémités du pipe. 0 = lecture, 1 = écriture
	// Stockera les 2 files descriptors
	pid_t cpid; //PID du processus enfant
	char buf; //stock 1 caractere à la fois pour l'afficher dans l'enfant

	assert(argc == 2);
	if (pipe(pipefd) == -1) //init pipe.
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	cpid = fork(); //crée le processus enfant
	if (cpid == -1) //fork == -1 == le fork a échoué
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (cpid == 0) //fork == 0 == processus enfant 
	{
		close(pipefd[1]); //l'enfant lit donc on peut fermé l'extrémité de l'écriture 
	  while (read(pipefd[0], &buf, 1) > 0) //lit caractere par caractere, et l'écrit.
			write(STDOUT_FILENO, &buf, 1);
		write(STDOUT_FILENO, "\n", 1);
		close(pipefd[0]);
		_exit(EXIT_SUCCESS);
	}
	else // fork > 0 == processus parent 
	{
		close(pipefd[0]); //parent ne lit pas donc on ferme.
		write(pipefd[1], argv[1], strlen(argv[1])); //écriture de la chaine passé en argument dans le pipe. 
		close(pipefd[1]); //on ferme aprés avoir écrit
		wait(NULL); //atend que l'enfant se termine 
		exit(EXIT_SUCCESS);
	}
}*/
