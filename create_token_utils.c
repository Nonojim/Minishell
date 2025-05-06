/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:11:59 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/06 02:50:31 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(int type, char *str)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->type = type;
	new_token->str = str;
	new_token->next = NULL;
	return (new_token);
}

void	add_token_end(t_token **token, t_token *new_token)
{
	t_token	*tmp;

	if (*token == NULL)
		*token = new_token;
	else
	{
		tmp = *token;
		while (tmp->next && tmp != NULL)
			tmp = tmp->next;
		tmp->next = new_token;
	}
}

void	print_token_list(t_token *token_list)
{
	while (token_list)
	{
		printf("[%d : %s] -> ", token_list->type, token_list->str);
		token_list = token_list->next;
	}
	printf("NULL\n");
}

void	free_token(t_token *token_list)
{
	t_token	*tmp;

	while (token_list)
	{
		tmp = token_list->next;
		free(token_list->str);
		free(token_list);
		token_list = tmp;
	}
}
