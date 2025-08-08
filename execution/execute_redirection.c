/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:00:27 by lduflot           #+#    #+#             */
/*   Updated: 2025/08/08 17:22:54 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*Applique toutes les redirs de l'AST,
Exe la cmd, et save les entrées/sortie.*/
int	execute_redirection_chain(t_treenode *node, char *line, t_ctx *ctx)
{
	int			saved_stdin;
	int			saved_stdout;
	int			status;
	t_treenode	*cmd;
	char		**tmp_argv;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	cmd = find_command_node(node);
	if (cmd)
		new_argv_cmd(node);
	status = apply_redirections(node, line, ctx);
	if (status != 0)
		return (dup_and_close(saved_stdin, saved_stdout), ctx->exit_code = 1);
	if (cmd && cmd->argv && cmd->argv[0])
		return (status = execute_simple_command(cmd, line, ctx), \
dup_and_close(saved_stdin, saved_stdout), status);
	tmp_argv = recup_all_argv_without_cmd(node);
	if (tmp_argv && tmp_argv[0])
	{
		status = create_and_exe_cmd(tmp_argv, line, ctx);
		return (dup_and_close(saved_stdin, saved_stdout), status);
	}
	return (dup_and_close(saved_stdin, saved_stdout), 0);
}

char	**recup_all_argv_without_cmd(t_treenode *node)
{
	char	**result;
	char	**curent;
	char	**merged;
	int		len_res;
	int		len_cur;

	result = NULL;
	curent = NULL;
	merged = NULL;
	len_res = 0;
	len_cur = 0;
	if (node->left && node->left->type == HERE_DOCUMENT)
		result = recup_all_argv_without_cmd(node->left);
	curent = copy_argv_in_newcmd(node->right->argv);
	if (!curent)
		return (result);
	if (result)
	{
		while (result[len_res])
			len_res++;
	}
	while (curent[len_cur])
		len_cur++;
	return (merged = create_new_node_arg(&len_res, &len_cur, result, curent));
}

char	**copy_argv_in_newcmd(char **argv)
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

char	**create_new_node_arg(int *len_res, int *len_cur,\
												char **result, char **curent)
{
	char	**merged;
	int		i;
	int		j;

	i = 0;
	j = 0;
	merged = malloc(sizeof(char *) * (*len_res + *len_cur + 1));
	if (!merged)
		return (result);
	while (j < *len_res)
		merged[i++] = result[j++];
	j = 0;
	while (j < *len_cur)
		merged[i++] = curent[j++];
	merged[i] = NULL;
	free(result);
	free(curent);
	return (merged);
}

int	create_and_exe_cmd(char **tmp_argv, char *line, t_ctx *ctx)
{
	int			status;
	t_treenode	cmd_test;

	cmd_test.type = WORD;
	cmd_test.argv = tmp_argv;
	cmd_test.str = tmp_argv[0];
	cmd_test.left = NULL;
	cmd_test.right = NULL;
	status = execute_node(&cmd_test, line, ctx);
	free_split(tmp_argv);
	return (status);
}
