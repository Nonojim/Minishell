/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:30:57 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/05 16:14:06 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_word_node(t_token **token_list);
t_treenode	*parse_word1(t_token **token_list);

t_treenode *parse_word_node(t_token **tokens)
{
	int	argc = 0;
	int	i = 0;
	t_token *tmp = *tokens;

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

	while (i < argc)
	{
		argv[i] = ft_strdup((*tokens)->str);
		*tokens = (*tokens)->next;
		i++;
	}
	argv[argc] = NULL;

	t_treenode *cmd = create_treenode(0, argv[0]);
	cmd->argv = argv;
	return cmd;
}

//t_treenode	*parse_word_node(t_token **token_list)
//{
//	t_treenode	*node;
//	t_token		*tmp;
//
//	node = NULL;
//	tmp = *token_list;
//	node = parse_word1(token_list);
//	if (node)
//		return (node);
//	*token_list = tmp;
//	free_treenode(node);
//	return (NULL);
//}
//
////[WORD token]
//t_treenode	*parse_word1(t_token **token_list)
//{
//	t_treenode	*node;
//
//	node = NULL;
//	return (node = create_branch_words(token_list));
//}
