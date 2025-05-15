/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:27:50 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/13 15:46:06 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
	https://www.howtogeek.com/438882/how-to-use-pipes-on-linux/ 
*/
//Exemple du man pipe :
// Creation d'un pipe.
// Le processus parents écrit "argv" dans le pipe
// Le processus enfant lit ce que le parent a écrit et l'affiche caractere par caractere sur la sortie standart (stdout).
int	main(int argc, char **argv)
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
}
