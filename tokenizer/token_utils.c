/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:56:21 by lduflot           #+#    #+#             */
/*   Updated: 2025/08/02 13:05:04 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_token	*create_token(int type, char *str)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
	{
		free(str);
		return (NULL);
	}
	new_token->type = type;
	new_token->str = str;
	new_token->next = NULL;
	return (new_token);
}

void	add_token_end(t_token **token, t_token *new_token)
{
	t_token	*tmp;

	if (!new_token)
		return ;
	if (*token == NULL)
	{
		*token = new_token;
		return ;
	}
	tmp = *token;
	while (tmp->next)
	{
		if (tmp == new_token)
			return ;
		tmp = tmp->next;
	}
	tmp->next = new_token;
}

void	print_token_list(t_token *token_list)
{
	int		i;
	char	*str;

	while (token_list)
	{
		str = token_list->str;
		printf("[%d : ", token_list->type);
		i = 0;
		while (str[i])
		{
			if (str[i] == '\n')
				printf("\\n");
			else if (str[i] == '\t')
				printf("\\t");
			else
				printf("%c", str[i]);
			i++;
		}
		printf("] -> ");
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
		if (token_list->str)
			free(token_list->str);
		free(token_list);
		token_list = tmp;
	}
}

t_token *exit_token(void)
{
	t_token *exit_token;

	exit_token = malloc(sizeof(t_token));
	if (!exit_token)
		return (NULL);
	ft_memset(exit_token, 0, sizeof(t_token));
	exit_token->str = ft_strdup("exit");
	return (exit_token);
}
