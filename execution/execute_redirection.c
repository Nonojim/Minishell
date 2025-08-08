/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:00:27 by lduflot           #+#    #+#             */
/*   Updated: 2025/08/08 14:40:00 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	redir_heredoc(t_treenode *node, t_ctx *ctx);
/*Applique toutes les redirs de l'AST,
Exe la cmd, et save les entrées/sortie.*/
char **copy_argv_hd_in_newcmd(char **argv);
char **recup_all_argv_hd(t_treenode *node)
{
  char    **result;
  char    **curent;
  char    **merged;
  int     len_res;
  int     len_cur;
  int     i;
  int     j;

  result = NULL;
  curent = NULL;
  merged = NULL;
  len_res = 0;
  len_cur = 0;
  i = 0;
  j = 0;
  if (node->left && node->left->type == HERE_DOCUMENT)
		result = recup_all_argv_hd(node->left);
  curent = copy_argv_hd_in_newcmd(node->right->argv);
	if (!curent)
		return (result);
  if (result)
  {
		while (result[len_res])
			len_res++;
  }
  while (curent[len_cur]) 
		len_cur++;
  merged = malloc(sizeof(char*) * (len_res + len_cur + 1));
  if (!merged)
		return (result);
  while (j < len_res)
	{
		merged[i] = result[j];
		i++;
		j++;
	}
  j = 0;
  while (j < len_cur)
	{
  	merged[i] = curent[j];
		i++;
		j++;
	}
  merged[i] = NULL;
  free(result);
  free(curent);
  return (merged);
}

char **copy_argv_hd_in_newcmd(char **argv)
{
	char	**new_argv;
	int		i;
	int		j;

	i = 0;
	j = 1;
	if (!argv || !argv[1])
		return (NULL);
	while (argv[j] != NULL)
		j++;
	new_argv = malloc(sizeof(char *) * (j + 1));
	if (!new_argv)
		return (NULL);
	j = 1;
	while (argv[j])
	{
		new_argv[i] = ft_strdup(argv[j]);
		i++;
		j++;
	}
	new_argv[i] = NULL;
	return (new_argv);
}

int	execute_redirection_chain(t_treenode *node, char *line, t_ctx *ctx)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;
	t_treenode	*cmd;
	char	**tmp_argv;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	cmd = find_command_node(node);
	if (cmd)
		new_argv_cmd(node);
	status = apply_redirections(node, line, ctx);
	if (status != 0)
	{
		dup_and_close(saved_stdin, saved_stdout);
		return (ctx->exit_code = 1);
	}
	if (cmd && cmd->argv && cmd->argv[0]) 
	{
		status = execute_simple_command(cmd, line, ctx);
		dup_and_close(saved_stdin, saved_stdout);
		return (status);
  }
  tmp_argv = recup_all_argv_hd(node);
  if (tmp_argv && tmp_argv[0]) 
	{
      t_treenode cmd_test;
			cmd_test.type  = WORD;
			cmd_test.argv  = tmp_argv;
			cmd_test.str   = tmp_argv[0];
			cmd_test.left  = NULL;
			cmd_test.right = NULL;
      status = execute_node(&cmd_test, line, ctx);
      free_split(tmp_argv);
      dup_and_close(saved_stdin, saved_stdout);
      return (status);
  }
	dup_and_close(saved_stdin, saved_stdout);
	return (0);
}

/*Parcours les node de redirs de manière récursive de gauche à droite*/
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
		return (redir_input(node, ctx));
	else if (node->type == HERE_DOCUMENT)
		return (redir_heredoc(node, ctx));
	else if (node->type == OUTPUT_REDIRECTION)
		return (redir_output(node, ctx));
	else if (node->type == APPEND_OUTPUT_REDIRECTION)
		return (redir_append(node, ctx));
	return (0);
}

int	redir_heredoc(t_treenode *node, t_ctx *ctx)
{
	int	pipefd[2];
	int	len;

	if (!node || !node->right || !node->right->str)
		return (ctx->exit_code = 1);
	if (pipe(pipefd) == -1)
		return (perror("pipe"), ctx->exit_code = 1);
	len = ft_strlen(node->right->str);
	if (write(pipefd[1], node->right->str, len) != len)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (perror("write"), ctx->exit_code = 1);
	}
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		close(pipefd[0]);
		return (perror("dup2"), ctx->exit_code = 1);
	}
	close(pipefd[0]);
	return (0);
}

/* Gestion de : <
Ouvre le fichier en lecture seul et le met à l'entrée standard*/
int	redir_input(t_treenode *node, t_ctx *ctx)
{
	int	fd;

	if (!node->right || !node->right->str)
		return (1);
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

/*Gestion : >
Ouvre ou crée le file en écriture et le met à la sortie standard
Supprime son contenu avec O_TRUNC*/
int	redir_output(t_treenode *node, t_ctx *ctx)
{
	int	fd;

	if (!node->right || !node->right->str)
		return (1);
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

/* Gestion de : >>
Ouvre ou crée le file et le met à la sortie standard
Ajoute du contenue à la fin avec O_APPEND*/
int	redir_append(t_treenode *node, t_ctx *ctx)
{
	int	fd;

	if (!node->right || !node->right->str)
		return (1);
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
