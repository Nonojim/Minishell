/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:57:53 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/26 17:01:53 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
	* STDIN_FILENO = 0 = Entrée standard (clavier, pipe, <)
	* STDOUT_FILENO = 1 = Sortie standard (écran, pipe, >)
	* STDERR_FILENO = 2 = Sortie d'erreur standard (écran)
	* 
	* Waitpid remplie un status(int). Les macros suivantes permettrent d'interprété ce status :
	* WIFEXITED (status) = Test si process c'est terminé normalement Return 1 (oui), 0 (non)
	*WEXITSTATUS(status) = récup le code de retour du fils
	* WIFSIGNALED(status) = return 1 si fils tué par un signal
	* WTERMSIG(status) = return num du signal
	*/


int execute_pipeline(t_treenode *node, t_token *token, char *line)
{
	int pipefd[2]; //stock les deux extrémités du pipe [0] = read [1] = write 
	pid_t pid1, pid2; //PID process enfant
	int status1, status2; //code de retour des 2 process 
	//on crée le pipe
	if (pipe(pipefd) == -1) //pipe non cré
		return (perror("pipe"), 1); 

	//premier fork (commande left)
	pid1 = fork();
	if (pid1 == -1)
		return (perror("fork1"), 1);
	if (pid1 == 0)
	{
		// Fils 1 : left side
		dup2(pipefd[1], STDOUT_FILENO); //redirige STDOUT vers entrée du pipe
		close(pipefd[0]); //fermeture de l'extrémité non utilisé 
		close(pipefd[1]); //ferme descripteur aprés redirection 
		exit(execute_node(node->left, token, line));
	}

	//deuxieme fork pour commande de droite
	pid2 = fork();
	if (pid2 == -1)
		return (perror("fork2"), 1);
	if (pid2 == 0)
	{
		// Fils 2 : right side
		dup2(pipefd[0], STDIN_FILENO); //redirige stdin vers la  sortie du pipe
		close(pipefd[0]);
		close(pipefd[1]);
		exit(execute_node(node->right, token, line)); 
	}

	// Parent ferme les deux extrémité du pipe (plus besoin maintenant)
	close(pipefd[0]);
	close(pipefd[1]);
	//attend de la fin des deux process 
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);

	int code_error;
	if (WIFEXITED(status2))
		code_error = WEXITSTATUS(status2);
	else
		code_error = 1;
	node->env = add_code_error(node->env, code_error);
	return (code_error); // On retourne le code du dernier
}
