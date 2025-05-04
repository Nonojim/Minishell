/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:23:42 by npederen          #+#    #+#             */
/*   Updated: 2025/05/04 19:15:32 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_istokenword(int c)
{
	if (c >= 33 && c <= 126 && c != 38 && c != 92 && c != 124 && c != 60 && c != 62 && c != 59 && c != 40 && c != 41 && c != 34 && c != 39 && c != ' ')
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
	
	token = malloc(sizeof(t_token));
	printf("%d , %d\n", BRACKETS_L, WORD);
	while (1)
	{
		start = 0;
		i = 0;
		line = readline("Minishell$ ");
		if (line == NULL)
			break;
		if(line)
			add_history(line);
		printf("%s\n", line);
		size_line = ft_strlen(line);
		printf("taille prompt: %d\n", size_line);
		printf("carac: %c\n", line[1]);
		if (line[i] != '\0')
		{
			while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
			{
				start++;
				i++;
			}
			while (line[i] != '\0' && ft_istokenword(line[i]) == 1)
				i++;
			str = ft_substr(line, start, i - start);
			printf("i = [%i]\n", i);
			printf("str = [%s]\n", str);
			token->str = str;
			printf("token->str = [%s]\n", token->str);
		}
		free(line);
	}
	return (0);
}
