/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:23:42 by npederen          #+#    #+#             */
/*   Updated: 2025/05/05 14:49:42 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Fonction lié à la création de token déplacé dans create_token_utils.c

int	ft_istokenword(int c)
{
	if (c == 38 || c == 92 || c == 124 || c == 60 || c == 62 || c == 59
		|| c == 40 || c == 41 || c == 34 || c == 39)
		return (0);
	if (c >= 33 && c <= 126)
		return (1);
	return (0);
}

//AJOUT0
int	is_operator_logical(char c)
{
	if (c == '|' || c == '&' || c == ';' || c == '<' || c == '>'
		|| c == '(' || c == ')')
	{
		return (1);
	}
	else
		return (0);
}
//AJOUT

//Readline leak ==296785==    still reachable: 214,430 bytes in 259 blocks
int	main(void)
{
	char	*line;
	int		size_line;
	int		start;
	int		i;
	t_token	*token;
	char	*str;

	while (1)
	{
		token = NULL;
		i = 0;
		start = 0;
	//	type = -1;
		line = readline("Minishell$ ");
		if (line == NULL)
			break ;
		if (line)
			add_history(line);
		printf("line = [%s]\n", line);
		size_line = ft_strlen(line);
		printf("taille prompt: %d\n", size_line);
		printf("carac: %c\n", line[1]);
		while (line[i] != '\0')
		{
			//AJOUT - Tokenise bien les operateurs logique.
			//MAIS, si double op tokénise et aprés repasse et retokénise le i+1;
			while (line[i] != '\0' && (line[i] == ' '
					|| line[i] == '\t' || line[i] == '\n'))
				i++;
			if (is_operator_logical(line[i]) == 1)
			{
				if (is_operator_logical(line[i + 1]) == 1)
				{
					str = ft_substr(line, i, 2);
					add_token_end(&token, create_token(OPERATOR, str));
					i++;
				}
				else
				{
					str = ft_substr(line, i, 1);
					add_token_end(&token, create_token(OPERATOR, str));
				}
			}
			//FIN_AJOUT
			start = i;
			while (line[i] != '\0' && ft_istokenword(line[i]) == 1)
				i++;
			str = ft_substr(line, start, i - start);
		//	printf("str = [%s]\n", str);
			if (ft_istokenword(*str) == 1)
			{
				add_token_end(&token, create_token(WORD, str));
			}
			else
			{
				i++;
			}
			print_token_list(token);
		}
		free_token(token);
		free(line);
	}
	return (0);
}
