/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:23:42 by npederen          #+#    #+#             */
/*   Updated: 2025/05/04 20:13:26 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *create_token(int type, char *str)
{
	t_token *new_token;

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
	t_token *tmp;

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

void print_token_list(t_token *token_list)
{
    while(token_list)
    {
        printf("[%d : %s] -> ", token_list->type, token_list->str);
        token_list = token_list->next;
    }
    printf("NULL\n");
}

void free_token(t_token *token_list)
{
	t_token *tmp;
	
	while (token_list)
	{
		tmp = token_list->next;
		//token_list = token_list->next;
		free(token_list->str);
		free(token_list);
		token_list = tmp;
	}
}

int	ft_istokenword(int c)
{
	if ( c == 38 || c == 92 || c == 124 || c == 60 || c == 62 || c == 59 || c == 40 
		|| c == 41 || c == 34 || c == 39)
		return (0);
	if (c >= 33 && c <= 126)
		return (1);
	return (0);
}

int	main(void)
{
	char	*line;
	int	size_line;
	int	start;
	int	i;
	t_token	*token;
	char	*str;
	
	while (1)
	{
		token = NULL;
		i = 0;
		start = 0;
		line = readline("Minishell$ ");
		// ==296785==    still reachable: 214,430 bytes in 259 blocks
		if (line == NULL)
			break;
		if(line)
			add_history(line);
		printf("line = [%s]\n", line);
		size_line = ft_strlen(line);
		printf("taille prompt: %d\n", size_line);
		printf("carac: %c\n", line[1]);
		while (line[i] != '\0')
		{
			while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
			{
				i++;
			}
			start = i;
			while (line[i] != '\0' && ft_istokenword(line[i]) == 1)
				i++;
			str = ft_substr(line, start, i - start);
			printf("str = [%s]\n", str);
			if (ft_istokenword(*str) == 1)
			{
				add_token_end(&token, create_token(WORD, str));
			}
			else
				i++;
			print_token_list(token);
		}
		free_token(token);
		free(line);
	}
	return (0);
}
