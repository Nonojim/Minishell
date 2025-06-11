/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:30:57 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/11 10:17:59 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_word_node(t_token **token_list);
t_treenode	*parse_word1(t_token **token_list);
int	parse_cmd(char *cmd);

t_treenode *parse_word_node(t_token **tokens)
{
	int	argc = 0;
	int	i = 0;
	t_token *tmp = *tokens;

	//printf("%p\n", (*tokens)->str);
	while (tmp != NULL
		&& (tmp->type == WORD
	|| tmp->type == EXPANSION
	|| tmp->type == SIMPLE_QUOTE
	|| tmp->type == DOUBLE_QUOTE))
	{
		argc++;
		tmp = tmp->next;
	}
	if (argc == 0)
		return NULL;

	char **argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return NULL;
	tmp = *tokens;
	//printf("%p\n", (*tokens)->str);
	while (i < argc)
	{
		argv[i] = ft_strdup((tmp)->str);
		//argv[i] = ft_strdup((*tokens)->str);
		//*tokens = (*tokens)->next;
		tmp = tmp->next;
		i++;
	}
	argv[argc] = NULL;
	//printf("%p\n", (*tokens)->str);
	t_treenode *cmd = create_treenode(0, argv[0]);
	cmd->argv = argv;
	if (parse_cmd(argv[0]) == 1)
	{
		printf("%s: command not found\n", argv[0]);
		free_treenode(cmd);
		return (NULL);
	}
	*tokens = tmp;
	return cmd;
}

int	parse_cmd(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (0);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (0);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (0);
	else if (ft_strcmp(cmd, "export") == 0)
		return (0);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (0);
	else if (ft_strcmp(cmd, "env") == 0)
		return (0);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (0);
	else
		return (1);
}
