/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:30:57 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/13 17:31:13 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_word_node(t_token **tokens);
t_treenode	*parse_word1(t_token **tokens);
int	parse_cmd(char *cmd, int *error);

t_treenode *parse_word_node(t_token **tokens)
{
	int	argc = 0;
	int	i = 0;
	t_token *tmp = *tokens;
	t_treenode *cmd_node;
	char	**argv;
	//static int	count = 0;

	if (parse_error(-1) == 1)
		return (NULL);
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
	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return NULL;
	tmp = *tokens;
	while (i < argc)
	{
		argv[i] = ft_strdup((tmp)->str);
		tmp = tmp->next;
		i++;
	}
	argv[argc] = NULL;
	cmd_node = create_treenode(0, argv[0]);
	cmd_node->argv = argv;
	*tokens = tmp;
	//count++;
//	printf("-%i-", count);
	return (cmd_node);
}


