/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:31:46 by lduflot           #+#    #+#             */
/*   Updated: 2025/08/08 14:15:05 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*Restaure les fd entrée et sortie*/
void	dup_and_close(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

/* Cherche dans l'AST le node cmd s'il existe
 Pour:
  - exe la commande une fois toutes les redis appliqués
  - dans new_argv_cmd: compter le nbr d'argv pour malloc un nouveau tableau
 */
t_treenode	*find_command_node(t_treenode *node)
{
	while (node && is_redirection(node->type))
		node = node->left;
	if (node && node->type == WORD)
		return (node);
	return (NULL);
}

/*Récupère les argv en trop d'une redirection 
* Les attributs au argv de la commande */
void	new_argv_cmd(t_treenode *redir_node)
{
	t_treenode	*cmd;
	int			i;
	char		**new_argv;

	cmd = find_command_node(redir_node);
	new_argv = create_new_array_cmd(redir_node, cmd);
	if (!new_argv)
		return ;
	i = 0;
	while (cmd->argv[i])
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	create_new_argv_cmd(new_argv, &i, redir_node);
	new_argv[i] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
}

/* Récupère le nombre total d'argv dans la cmd plus ceux en trop des redir
Afin de créer un nouveau tab d'argv
i = 1 pour sauter le file associé à la redir*/
char	**create_new_array_cmd(t_treenode *redir_node, t_treenode *cmd)
{
	char		**new_argv;
	int			total_argv;
	int			i;

	i = 0;
	if (!cmd || !cmd->argv)
		return (NULL);
	while (cmd->argv[i])
		i++;
	total_argv = i;
	while (redir_node && is_redirection(redir_node->type))
	{
		i = 1;
		if (redir_node->right && redir_node->right->argv)
		{
			while (redir_node->right->argv[i++])
				total_argv++;
		}
		redir_node = redir_node->left;
	}
	new_argv = malloc(sizeof(char *) * (total_argv + 1));
	if (!new_argv)
		return (NULL);
	return (new_argv);
}

/*Crée le nouveau tableau d'argv de cmd en se déplacant de gauche à droite
dans les redir 
j = 1 pour sauter le file associé à la redir*/
void	create_new_argv_cmd(char **new_argv, int *i, t_treenode *node)
{
	int	j;

	if (!node || !is_redirection(node->type))
		return ;
	create_new_argv_cmd(new_argv, i, node->left);
	j = 1;
	if (node->right && node->right->argv)
	{
		while (node->right->argv[j])
		{
			new_argv[*i] = node->right->argv[j];
			(*i)++;
			j++;
		}
		node->right->argv[1] = NULL;
	}
}
