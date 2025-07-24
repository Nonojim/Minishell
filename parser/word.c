/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:30:57 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/22 19:55:48 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_word_node(t_token **tokens);
t_treenode	*create_word_node(int *argc, t_token *tmp, t_token **tokens);

t_treenode	*parse_word_node(t_token **tokens)
{
	int			argc;
	t_token		*tmp;

	argc = 0;
	tmp = *tokens;
	if (parse_error(-1) == 1)
		return (NULL);
	while (tmp != NULL && is_word_type(tmp->type))
	{
		argc++;
		tmp = tmp->next;
	}
	if (argc == 0)
		return (NULL);
	return (create_word_node(&argc, tmp, tokens));
}

t_treenode	*create_word_node(int *argc, t_token *tmp, t_token **tokens)
{
	int			i;
	char		**argv;
	t_treenode	*cmd_node;

	i = 0;
	cmd_node = NULL;
	argv = malloc(sizeof(char *) * (*argc + 1));
	if (!argv)
		return (NULL);
	tmp = *tokens;
	while (i < *argc)
	{
		argv[i] = ft_strdup((tmp)->str);
		tmp = tmp->next;
		i++;
	}
	argv[*argc] = NULL;
	cmd_node = create_treenode(0, NULL);
	cmd_node->argv = argv;
	cmd_node->str = ft_strdup(argv[0]);
	*tokens = tmp;
	return (cmd_node);
}
