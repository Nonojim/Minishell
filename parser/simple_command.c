/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:29:26 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/04 23:12:18 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_simple_command_node(t_token **token_list);
t_treenode	*parse_simple_command1(t_token **token_list);
t_treenode	*parse_simple_command2(t_token **token_list);

t_treenode	*parse_simple_command_node(t_token **token_list)
{
	t_treenode	*node;
	t_token		*tmp;

	node = NULL;
	tmp = *token_list;
	node = parse_simple_command1(token_list);
	if (node)
		return (node);
	*token_list = tmp;
//	free_treenode(node);
	node = parse_simple_command2(token_list);
	if (node)
		return (node);
	*token_list = tmp;
	//free_treenode(node);
	return (NULL);
}

int	is_redirection(int type)
{
return (type == INPUT_REDIRECTION
		|| type == OUTPUT_REDIRECTION
		|| type == HERE_DOCUMENT
		|| type == APPEND_OUTPUT_REDIRECTION);
}
//no priorité ds les redirection, prio dans le sens de lecture (gauche à droite)
t_treenode	*parse_simple_command1(t_token **token_list)
{
	//t_treenode	*node;
	//t_treenode	*new_node;
	t_treenode	*left;

	//node = NULL;
	//new_node = NULL;
	left = NULL;
	left = parse_word_node(token_list);
	if (left == NULL)
		return (NULL);
	while (*token_list != NULL && is_redirection((*token_list)->type))
	{
		t_token *redir_tok = *token_list;
		*token_list = (*token_list)->next;
		if (*token_list == NULL || (*token_list)->type != WORD)
			return NULL;
		t_token *file = *token_list;
		*token_list = (*token_list)->next;
		t_treenode *redir = create_treenode(redir_tok->type, redir_tok->str);
		redir->left = left;
		redir->right = create_treenode(file->type, file->str);
		left = redir;
		//new_node = parse_redirection_node(token_list);
		//pas de création de node ici puisqu'il est déjà crer dans redirection sinon le crée en double
		/*t_token *create_node = *token_list;
		*token_list = (*token_list)->next;
		if ((right = parse_simple_command_node(token_list)) == NULL)
			return (NULL);
		node = create_treenode(create_node->type, create_node->str);
		node->left = left;
		node->right = right;
		return (node);*/
	}
	return (left);
}

t_treenode	*parse_simple_command2(t_token **token_list)
{
	t_treenode	*node;

	node = NULL;
	return (node = parse_word_node(token_list));
}
