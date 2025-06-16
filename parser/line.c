/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:27:07 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/16 19:51:11 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_line_node(t_token **tokens);
t_treenode	*parse_line1(t_token **tokens);
t_treenode	*parse_line2(t_token **tokens);
t_treenode	*parse_line3(t_token **tokens);

/*
	parse_error(0) = remet à 0 la static;
	dernier if = s'il reste des tokens exemple test )
*/
//t_treenode	*parse_line_node(t_token **tokens)
//{
//	t_token		*tmp;
//	t_treenode	*line_node;
//
//	tmp = *tokens;
//	line_node = NULL;
//	// parse_error(0); -> mis dans main car pour subshell remettez tout a zéro
//	if (*tokens == NULL || tokens == NULL)
//		return (NULL);
//	line_node = parse_line1(tokens);
//	if (parse_error(-1) == 1)
//		return (NULL);
//	if (line_node == NULL)
//	{
//		*tokens = tmp;
//		line_node = parse_line2(tokens);
//		if (parse_error(-1) == 1)
//			return (NULL);
//	}
//	if (line_node == NULL)
//	{
//		*tokens = tmp;
//		line_node = parse_line3(tokens);
//		if (parse_error(-1) == 1)
//			return (NULL);
//	}
//	/*	if (line_node != NULL && *tokens != NULL) ->mis dans mains car pour subshell faisait tout planter ici
//		{
//			print_error(*tokens);
//			free_treenode(line_node);
//			return (NULL);
//		}*/
//	return (line_node);
//}
t_treenode	*parse_line_node(t_token **tokens)
{
	t_token		*tmp;
	t_treenode	*line_node;

	tmp = *tokens;
	line_node = NULL;
	if (*tokens == NULL || tokens == NULL)
		return (NULL);
	line_node = parse_line1(tokens);
	if (parse_error(-1) == 1)
		return (NULL);
	if (line_node == NULL)
	{
		*tokens = tmp;
		line_node = parse_line2(tokens);
		if (parse_error(-1) == 1)
			return (NULL);
	}
	if (line_node == NULL)
	{
		*tokens = tmp;
		line_node = parse_line3(tokens);
		if (parse_error(-1) == 1)
			return (NULL);
	}
	return (line_node);
}

//<logical_or> (";" <logical_or>)*
t_treenode	*parse_line1(t_token **tokens)
{
	t_treenode	*left;
	t_treenode	*right;
	t_treenode	*semicolon_node;
	t_token		*semicolon_token;

	left = parse_logical_or_node(tokens);
	if (left == NULL && (*tokens)->type == SEMICOLON)
		return (printerror_then_return_null(tokens));
	if (left == NULL)
		return (NULL);
	if (*tokens == NULL || (*tokens)->type != SEMICOLON)
		return (free_then_return_null(left));
	semicolon_token = *tokens;
	*tokens = (*tokens)->next;
	if (*tokens == NULL)
		return (free_then_return_null(left));
	right = parse_line_node(tokens);
	if (right == NULL)
		return (free_then_return_null(left));
	semicolon_node = create_treenode(semicolon_token->type,
			semicolon_token->str);
	semicolon_node->left = left;
	semicolon_node->right = right;
	return (semicolon_node);
}

//<logical_or> ";"
t_treenode	*parse_line2(t_token **tokens)
{
	t_treenode	*left;
	t_treenode	*semicolon_node;
	t_token		*semicolon_token;

	left = NULL;
	semicolon_node = NULL;
	left = parse_logical_or_node(tokens);
	if (left == NULL)
		return (NULL);
	if (*tokens == NULL || (*tokens)->type != SEMICOLON)
		return (free_then_return_null(left));
	semicolon_token = *tokens;
	*tokens = (*tokens)->next;
	semicolon_node = create_treenode(semicolon_token->type,
			semicolon_token->str);
	semicolon_node->left = left;
	semicolon_node->right = NULL;
	return (semicolon_node);
}

//<logical_or>
t_treenode	*parse_line3(t_token **tokens)
{
	t_treenode	*or_node;

	or_node = NULL;
	return (or_node = parse_logical_or_node(tokens));
}
