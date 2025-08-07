/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:55:01 by lduflot           #+#    #+#             */
/*   Updated: 2025/08/07 20:07:51 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
	* Code erreur pour la var $? 
	* (Convention Posix & Bash)
	* Valeur comprise entre 0 et 255.
	* 0 = Succés 
	* 1 = Erreur général
	* 2 = Mauvais usage commande, erreur syntaxe
	* 126 = Command trouvé mais non exe
	* 127 = Command not found
	* 128 = Mauvais usage de exit (ex: exit -1, exit avec trop d'arguments)
	* 130 = Arret avec Ctrl+C
	* 131 = Arret avec Ctrl+\
*/

void	execute_tree(t_treenode *tree, char *line, t_ctx	*ctx)
{
	ctx->exit_code = execute_node(tree, line, ctx);
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
//	printf("new argv = %s ;  %s", new_argv[0], new_argv[1]);
	return (new_argv);
}

int    execute_node(t_treenode *node, char *line, t_ctx *ctx)
{
 if (!node)
     return (1);
 if (node->type == WORD || node->type == PIPE)
     return (execute_node_simple(node, line, ctx));
 else if (node->type == LOGICAL_AND || node->type == LOGICAL_OR
     || node->type == SEMICOLON)
     return (execute_node_logical(node, line, ctx));
 else if (node->type == HERE_DOCUMENT
     || node->type == INPUT_REDIRECTION
     || node->type == OUTPUT_REDIRECTION
     || node->type == APPEND_OUTPUT_REDIRECTION
     || node->type == SUBSHELL)
     {
         if (node->type == HERE_DOCUMENT && node->right && ft_strcmp(node->right->str, "") == 0 && !node->left)
         {
             execute_node_redir(node, line, ctx);
             return(execute_node(node->right, line, ctx));
         }
				else if (
			(node->type == HERE_DOCUMENT
			&& node->right 
			&& node->right->argv 
			&& node->right->argv[1]) 
			||(node->type == HERE_DOCUMENT
			&& node->left
			&& node->left->type == HERE_DOCUMENT))
				{
					if (node->left && node->type == HERE_DOCUMENT)
						node = node->left;
					t_treenode *cmd_test = NULL;
					cmd_test = malloc(sizeof(t_treenode));
					if (!cmd_test)
						return (ctx->exit_code = 1);
					cmd_test->type = WORD;
					//cmd_test->argv = save_cmd;
					cmd_test->argv = copy_argv_hd_in_newcmd(node->right->argv);
				if (!cmd_test->argv)
				{
					free(cmd_test);
					return (ctx->exit_code = 0);
				}
					cmd_test->str = ft_strdup(cmd_test->argv[0]);
					//	printf("cmd = %s , %s ", cmd_test->argv[0], cmd_test->argv[1]);
					cmd_test->left = node;
					int exit_code = 0;
					exit_code = execute_node(cmd_test, line, ctx);
					free(cmd_test->str);
					free(cmd_test);
					return (exit_code);
			}
			return (execute_node_redir(node, line, ctx));
   	  }
		 else
    	 return (1);
}

int	execute_node_simple(t_treenode *node, char *line, t_ctx *ctx)
{
	if (node->type == WORD)
		return (execute_simple_command(node, line, ctx));
	else if (node->type == PIPE)
	{
		expanse_ast(node, ctx);
		return (execute_pipeline(node, line, ctx));
	}
	return (1);
}

int	execute_node_logical(t_treenode *node, char *line, t_ctx *ctx)
{
	if (node->type == LOGICAL_AND)
	{
		if (execute_node(node->left, line, ctx) == 0)
		{
			ctx->exit_code = execute_node(node->right, line, ctx);
			return (ctx->exit_code);
		}
	}
	else if (node->type == LOGICAL_OR)
	{
		if (execute_node(node->left, line, ctx) != 0)
			ctx->exit_code = execute_node(node->right, line, ctx);
		return (ctx->exit_code);
	}
	else if (node->type == SEMICOLON)
	{
		execute_node(node->left, line, ctx);
		ctx->exit_code = execute_node(node->right, line, ctx);
		return (ctx->exit_code);
	}
	ctx->exit_code = 1;
	return (ctx->exit_code);
}

int	execute_node_redir(t_treenode *node, char *line, t_ctx *ctx)
{
	if (node->type == INPUT_REDIRECTION
		|| node->type == OUTPUT_REDIRECTION
		|| node->type == APPEND_OUTPUT_REDIRECTION
		|| node->type == HERE_DOCUMENT)
	{
		expanse_ast(node, ctx);
		return (execute_redirection_chain(node, line, ctx));
	}
	else if (node->type == SUBSHELL)
		return (execute_subshell_node(node, line, ctx));
	return (1);
}
