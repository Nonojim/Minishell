/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:25:50 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/27 13:49:52 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
Add command exit for quit programm properly during the test ./minishell
*/
/*
	* exit [n]
	* Si n == NULL quitte avec code actuel $?
	* Si n == non num = numeric argument required exit : 2
	* Si n + 1 != NULL = too many arguments ne quitte pas return 1
	*
	*/

long long 	ft_atoll(const char *nptr);
int	is_numeric_exit(char *argv);

int	ft_exit(char *line, t_token *token, t_treenode *ast)
{
	int	code_error;
	
	if (ast->argv[1])
	{
		if (!is_numeric_exit(ast->argv[1]))
		{
			printf("exit\n");
			printf("Minishell: exit: %s: numeric argument required\n", ast->argv[1]);
			free_token(token);
			free(line);
			free_env_list(ast->env);
			free_treenode(ast);
			rl_clear_history();
			exit(255);
		}
		else if (ast->argv[2])
		{
			printf("Minishell: exit: too many arguments\n");
			code_error = 1;
			ast->env = add_code_error(ast->env, code_error);
			return (code_error);
		}
		else
		{
			code_error = ft_atoi(ast->argv[1]) % 256; //quand on fait exit 1000 error = 232 donc 1000 % 256. Le code de sortie étant limité à 8 bits = 255 max. Bash fait un modulo de 256 pour avoir un affichage correct. 
		}
	}
	else
		code_error = 0;
	free_token(token);
	free(line);
	free_env_list(ast->env);
	free_treenode(ast);
	rl_clear_history();
	exit(code_error);
}

int	is_numeric_exit(char *argv)
{
	int i = 0;
//	int	sign = 1;
	//int	len;
	char	*nb;
	char	*max = "9223372036854775807";
	char	*min = "9223372036854775808"; 

	if (!argv || argv[0] == '\0')
		return (0);
	if (argv[i] == '+' || argv[i] == '-')
	{
			i++;
	}
	if (!argv[i])
		return (0);

	while (argv[i])
	{
		if (!ft_isdigit(argv[i]))
			return (0);
		i++;
	}
	if (argv[0] == '+' || argv[0] == '-')
		nb = &argv[1]; //on saute le sign
	else
		nb = argv;
	if (ft_strlen(nb) > 19) //LLONG_MAX = 19 chiffres
		return (0);
	if (ft_strlen(nb) == 19)
	{
		if (argv[0] == '-')
		{
			if (ft_strcmp(nb, min) > 0)
				return (0);
		}
		else
		{
			if (ft_strcmp(nb, max) > 0)
				return (0);
		}
	}
	return (1);}
