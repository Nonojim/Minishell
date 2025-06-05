/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:29:26 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/05 19:48:16 by npederen         ###   ########.fr       */
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
	node = parse_simple_command2(token_list);
	if (node)
		return (node);
	*token_list = tmp;
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
//<word> <redirection> word
t_treenode	*parse_simple_command1(t_token **token_list)
{
	t_token		*redir_tok;
	t_token		*file;
	t_treenode	*left;
	t_treenode	*redir;

	redir = NULL;
	left = NULL;
	left = parse_word_node(token_list);
	if (left == NULL)
		return (NULL);
	if (*token_list == NULL || !is_redirection((*token_list)->type))
	{
		free_treenode(left);
		return (NULL);
	}
	while (*token_list != NULL && is_redirection((*token_list)->type))
	{
		redir_tok = *token_list;
		*token_list = (*token_list)->next;
		if (*token_list == NULL || (*token_list)->type != WORD)
		{
			free_treenode(left);
			printf("syntax error near unexpected token `newline'\n");
			return NULL;
		}
		file = *token_list;
		*token_list = (*token_list)->next;
		redir = create_treenode(redir_tok->type, redir_tok->str);
		if (!redir)
		{
			//free_treenode(left);
			return (NULL);
		}
		redir->left = left;
		redir->right = create_treenode(file->type, file->str);
		if (!redir->right)
		{
			//free_treenode(left);
			//free_treenode(redir);
			return (NULL);
		}
		left = redir;
	}
	return (left);
}

//<word>
t_treenode	*parse_simple_command2(t_token **token_list)
{
	t_treenode	*node;

	node = NULL;
	return (node = parse_word_node(token_list));
}
