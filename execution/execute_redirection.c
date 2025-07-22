/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:00:27 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/22 17:53:08 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"


t_treenode	*find_command_node(t_treenode *node);

/*Récupère les argv en trop d'une redirection 
* Les attributs au argv de la commande */
void	new_argv_cmd(t_treenode *redir_node)
{
	t_treenode	*cmd_node;
	t_treenode	*node;
	int			cmd_argc;
	int			total_argc;
	int			i;
	char		**new_argv;

	cmd_node = find_command_node(redir_node);
	if (!cmd_node || !cmd_node->argv)
		return ;
	cmd_argc = 0;
	while (cmd_node->argv[cmd_argc])
		cmd_argc++;
	total_argc = cmd_argc;
	node = redir_node;
	while (node && (node->type == INPUT_REDIRECTION
			|| node->type == OUTPUT_REDIRECTION
			|| node->type == APPEND_OUTPUT_REDIRECTION))
	{
		i = 1;
		if (node->right && node->right->argv)
		{
			while (node->right->argv[i])
			{
				total_argc++;
				i++;
			}
		}
		node = node->left;
	}
	new_argv = malloc(sizeof(char *) * (total_argc + 1));
	if (!new_argv)
		return ;
	i = 0;
	while (cmd_node->argv[i])
	{
		new_argv[i] = cmd_node->argv[i];
		i++;
	}
	node = redir_node;
	while (node && (node->type == INPUT_REDIRECTION
			|| node->type == OUTPUT_REDIRECTION
			|| node->type == APPEND_OUTPUT_REDIRECTION))
	{
		int j = 1;
		if (node->right && node->right->argv)
		{
			while (node->right->argv[j])
			{
				new_argv[i++] = node->right->argv[j];
				j++;
			}
			node->right->argv[1] = NULL;
		}
		node = node->left;
	}
	new_argv[i] = NULL;
	free(cmd_node->argv);
	cmd_node->argv = new_argv;
}


t_treenode	*find_command_node(t_treenode *node)
{
	while (node && (node->type == OUTPUT_REDIRECTION
			|| node->type == APPEND_OUTPUT_REDIRECTION
			|| node->type == INPUT_REDIRECTION))
		node = node->left;
	return (node);
}

int	apply_redirections(t_treenode *node, char *line, t_ctx *ctx)
{
	int	status;

	status = 0;
	if (!node)
		return (1);
	if (node->left)
		status = apply_redirections(node->left, line, ctx);
	if (status != 0)
		return (status);
	if (node->type == INPUT_REDIRECTION)
		return (redir_input(node, line, ctx));
	else if (node->type == OUTPUT_REDIRECTION)
		return (redir_output(node, line, ctx));
	else if (node->type == APPEND_OUTPUT_REDIRECTION)
		return (redir_append(node, line, ctx));
	return (0);
}

void	dup_and_close(int	saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

int	execute_redirection_chain(t_treenode *node, char *line, t_ctx *ctx)
{
	int			saved_stdin;
	int			saved_stdout;
	int			status;
	t_treenode	*cmd;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	new_argv_cmd(node);
	status = apply_redirections(node, line, ctx);
	if (status != 0)
	{
		ctx->exit_code = 1;
		dup_and_close(saved_stdin, saved_stdout);
		return (1);
	}
	cmd = find_command_node(node);
	if (!cmd || !cmd->argv || !cmd->argv[0])
	{
		dup_and_close(saved_stdin, saved_stdout);
		return (0);
	}
	status = execute_node(cmd, line, ctx);
	dup_and_close(saved_stdin, saved_stdout);
	return (status);
}

int	redir_input(t_treenode *node, char *line, t_ctx *ctx)
{
	int	fd;

	(void)line;
	fd = open(node->right->str, O_RDONLY);
	if (fd < 0)
	{
		ft_fprintf(2, "minishell: %s: %s\n", node->right->str, strerror(errno));
		ctx->exit_code = 1;
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	redir_output(t_treenode *node, char *line, t_ctx *ctx)
{
	int	fd;

	(void)line;
	fd = open(node->right->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_fprintf(2, "minishell: %s: %s\n", node->right->str, strerror(errno));
		ctx->exit_code = 1;
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	redir_append(t_treenode *node, char *line, t_ctx *ctx)
{
	int	fd;

	(void)line;
	fd = open(node->right->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_fprintf(2, "minishell: %s: %s\n", node->right->str, strerror(errno));
		ctx->exit_code = 1;
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
