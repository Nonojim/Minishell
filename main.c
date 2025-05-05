/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:23:42 by npederen          #+#    #+#             */
/*   Updated: 2025/05/05 21:57:54 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_istokenword(int c)
{
	if (c == 38 || c == 92 || c == 124 || c == 60 || c == 62 || c == 59
		|| c == 40 || c == 41 || c == 34 || c == 39)
		return (0);
	if (c >= 33 && c <= 126)
		return (1);
	return (0);
}

int	is_operator_logical(char c)
{
	if (c == '|' || c == '&' || c == ';' || c == '<' || c == '>'
		|| c == '(' || c == ')')
	{
		return (c);
	}
	else
		return (0);
}

int	is_ok_double(char c)
{
	if (c == '|' || c == '&' || c == '<' || c == '<')
		return (1);
	else
		return (0);
}

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
			while (line[i] != '\0' && (line[i] == ' '|| line[i] == '\t' || line[i] == '\n'))
				i++;
			start = i;
			if (line[i] == '\'' && line[i])
			{
				while (line[i] == '\'')
					i++;
				start = i;
				while (line[i] && line[i] != '\'')
					i++;
				str = ft_substr(line, start, i - start);
				add_token_end(&token, create_token(WORD, str));
				while (line[i] == '\'')
					i++;	
			}
			else if (is_operator_logical(line[i]) == line[i] && line[i])
			{
				if (is_operator_logical(line[i + 1]) == line[i] && is_ok_double(line[i])  == 1)
				{
					str = ft_substr(line, start, 2);
					add_token_end(&token, create_token(OPERATOR, str));
					i += 2;
				}
				else
				{
					str = ft_substr(line, start, 1);
					add_token_end(&token, create_token(OPERATOR, str));
					i++;
				}
			}
			else if (line[i] != '\0' && ft_istokenword(line[i]) == 1)
			{
				while (line[i] != '\0' && ft_istokenword(line[i]) == 1)
					i++;
				str = ft_substr(line, start, i - start);
				if (ft_istokenword(*str) == 1)
					add_token_end(&token, create_token(WORD, str));
				else
					i++;
			}
		}
		print_token_list(token);
		free_token(token);
		free(line);
	}
	//rl_clear_history();
	return (0);
}
