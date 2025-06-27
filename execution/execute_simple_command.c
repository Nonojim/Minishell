/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:58:21 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/26 17:30:10 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern char	**environ;
//Accede à une variable globale déclarée ailleur dans une lib, celle-ci contiens toutes les variables d'env. Même chose que faire : int maint(int argc, char **argv, char **envp).


int	execute_simple_command(t_treenode *node, t_token *token, char *line)
{
	pid_t	pid;
	char	*cmd;
	int		status;
	char	*cmd_path;
	int	code_error;
	(void)token;
	(void)line;

	if (!node || !node->str || !node->argv)
	{
		node->env = add_code_error(node->env, 1);
		return (1);
	}
	cmd = node->argv[0];
	if (ft_strcmp(cmd, "echo") == 0)
	{
		code_error = ft_echo(node);
		node->env = add_code_error(node->env, code_error);
		return (code_error);
	}
	else if (ft_strcmp(cmd, "pwd") == 0)
	{
		code_error = ft_pwd(node);
		node->env = add_code_error(node->env, code_error);
		return (code_error);
	}
	else if (ft_strcmp(cmd, "cd") == 0)
	{
		code_error = ft_cd(node);
		node->env = add_code_error(node->env, code_error);
		return (code_error);
	}
	else if (ft_strcmp(cmd, "export") == 0)
	{
		code_error = ft_export(node);
		node->env = add_code_error(node->env, code_error);
		return (code_error);
	}
	else if (ft_strcmp(cmd, "unset") == 0)
	{
		code_error = ft_unset(node);
		node->env = add_code_error(node->env, code_error);
		return (code_error);
	}
	else if (ft_strcmp(cmd, "env") == 0)
	{
		code_error = ft_env(node->env);
		node->env = add_code_error(node->env, code_error);
		return (code_error);
	}
	else if (ft_strcmp(cmd, "exit") == 0)
	{
		code_error = ft_exit(line, token, node);
		node->env = add_code_error(node->env, code_error);
		return(code_error);
	}
	pid = fork(); // crée processus enfant 
	if (pid == 0) //enfant
	{
		//on recherche la cmd dans les bin de path
		cmd_path = NULL; //stok le chemin de la commande
		cmd_path = find_cmd_path(cmd, node->env); //recherche de la cmd
		if (!cmd_path) //pas de cmd trouvé 
		{
			printf("%s: command not found\n", node->argv[0]);
			exit(127); //on quitte l'enfant//code erreur command not found
		}
		// Enfant : on exécute la commande
	//	printf("path: %s\n", cmd_path);
		execve(cmd_path, node->argv, environ); //commande est trouvé donc on l'exe
		free(cmd_path);
		exit(126); //cmd trouve mais non executable code 126 //si exe echou on quitte le processus enfant 
	}
	else if (pid > 0) //le daron
	{
		waitpid(pid, &status, 0); //on attend la fin du processus enfant
		if (WIFEXITED(status)) //si l'enfant c'est normalement terminé 
			code_error = (WEXITSTATUS(status)); //on retourne son code de retour
		else
			code_error = 1;
		node->env = add_code_error(node->env, code_error);
		return (code_error); //sinon erreur 
	}
	else
	{
		perror("fork"); //affiche strerror(errno) = message d'erreur
		node->env = add_code_error(node->env, 1);
		return (1);
	}
	return (0);
}

//FREE_SPLIT MAYBE ?
char	*find_cmd_path(char *cmd, t_env *env_list)
{
	t_env	*path_node;
	char	**paths;
	int		i;
	char	*tmp;
	char	*cmd_path;

	//on cherche PATH dans la liste
	//path_node->value "/usr/local/bin: blablabla"
	path_node = find_node(env_list, "PATH");
	if (!path_node || !path_node->value)
		return (NULL);
	//on découpe le path en morceau aprés chaque :
	paths = ft_split(path_node->value, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i]) //on teste chaque path
	{
		tmp = ft_strjoin(paths[i], "/"); //on rajoute / a la fin du chemin ex: /bin devient /bin/
		cmd_path = ft_strjoin(tmp, cmd); //on rajoute le nom de cmd à la fin ex: /bin/ls
		free(tmp);
		//acces (pathname, mode) mode = F_OK (existe), R_OK (lisible), W_OK (écrivable), X_OK(exe)
		if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) == 0)
		{
			free_split(paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++; //si commande non trouvé dans ce path on passe au path suivant ...
	}
	free_split(paths);
	return (NULL);
}

void	free_split(char	**split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split[i]);
	free(split);
}
