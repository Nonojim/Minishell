/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:23:42 by npederen          #+#    #+#             */
/*   Updated: 2025/05/06 10:59:21 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TOKENS ASCII : | = 124 | || = 124,124 | && = 38,38 | ; = 59 | < = 60 | << = 60,60 | > = 62
// | >> = 62,62 | ' = 39 | " = 34 | ( = 40 | ) = 41 | $ = 36 | ~ = 126

int	ft_istokenword(int str)
{
	if (str == 38 || str == 92 || str == 124 || str == 60 || str == 62 || str == 59
		|| str == 40 || str == 41 || str == 34 || str == 39)
		return (0);
	if (str >= 33 && str <= 126)
		return (1);
	return (0);
}

int	is_operator_logical(char str)
{
	if (str == '|' || str == '&' || str == ';' || str == '<' || str == '>'
		|| str == '(' || str == ')')
	{
		return (str);
	}
	else
		return (0);
}

int	is_ok_double(char str)
{
	if (str == '|' || str == '&' || str == '<' || str == '<')
		return (1);
	else
		return (0);
}

//commande nvim pour changer mon ancien char c en char str :%s/\<c\>/str/g
int	type_token(char *str)
{
	if (str[0] == '|' && str[1] == '|' )
		return (LOGICAL_OR);
	else if (str[0] == '>' && str[1] == '>')
		return (OUTPUT_REDIRECTION);
	else if (str[0] == '<' && str[1] == '<')
		return (APPEND_OUTPUT_REDIRECTION);
	else if (str[0] == '&' && str[1] == '&')
		return (LOGICAL_AND);
	else if (str[0] == '|')
		return (PIPE);
	else if (str[0] == ';')
		return (SEMICOLON);
	else if (str[0] == '<')
		return (INPUT_REDIRECTION);
	else if (str[0] == '>')
		return (HERE_DOCUMENT);
	else if (str[0] == '\'')
		return (SIMPLE_QUOTE);
	else if (str[0] == '"')
		return (DOUBLE_QUOTE);
	else if (str[0] == '(')
		return (BRACKETS_R);
	else if (str[0] == ')')
		return (BRACKETS_L);
	else if (str[0] == '~')
		return (TILDE);
	else if (*str == '$')
		return (ENV_VAR);
	else
		return (WORD);
}

//Readline leak ==296785==    still reachable: 214,430 bytes in 259 blocks
int	main(void)
{
	char	*line;
//	int		size_line;
	int		start;
	int		i;
	t_token	*token;
	char	*str;
	int	type;

	while (1)
	{
		token = NULL;
		i = 0;
		start = 0;
		type = -1;
		line = readline("Minishell$ ");
		if (line == NULL)
			break ;
		if (line)
			add_history(line);
 		printf("line = [%s]\n", line);
		//size_line = ft_strlen(line);
		//printf("taille prompt: %d\n", size_line);
		//printf("carac: %str\n", line[1]);
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
				type = type_token(str);
				add_token_end(&token, create_token(type, str));
				while (line[i] == '\'')
					i++;
			}
			else if (is_operator_logical(line[i]) == line[i] && line[i])
			{
				if (is_operator_logical(line[i + 1]) == line[i] && is_ok_double(line[i])  == 1)
				{
					str = ft_substr(line, start, 2);
					type = type_token(str);
					add_token_end(&token, create_token(type, str));
					i += 2;
				}
				else
				{
					str = ft_substr(line, start, 1);	
					type = type_token(str);
					add_token_end(&token, create_token(type, str));
					i++;
				}
			}
			else if (line[i] != '\0' && ft_istokenword(line[i]) == 1)
			{
				while (line[i] != '\0' && ft_istokenword(line[i]) == 1)
					i++;
				str = ft_substr(line, start, i - start);
				if (ft_istokenword(*str) == 1)
				{
					type = type_token(str);
					add_token_end(&token, create_token(type, str));
				}
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
