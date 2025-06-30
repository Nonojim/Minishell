/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:25:50 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/30 11:57:22 by lduflot          ###   ########.fr       */
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
code_error = ft_atoi(ast->argv[1]) % 256; 
//quand on fait exit 1000 error = 232 donc 1000 % 256. 
Le code de sortie étant limité à 8 bits = 255 max. 
Bash fait un modulo de 256 pour avoir un affichage correct. 
*/

int	ft_exit(char *line, t_token *token, t_treenode *ast)
{
	int	code_error;

	if (ast->argv[1])
	{
		if (!is_numeric_exit(ast->argv[1]))
			error_numeric_exit(token, line, ast);
		else if (ast->argv[2])
		{
			printf("Minishell: exit: too many arguments\n");
			code_error = 1;
			ast->env = add_code_error(ast->env, code_error);
			return (code_error);
		}
		else
			code_error = ft_atoi(ast->argv[1]) % 256;
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

void	error_numeric_exit(t_token *token, char *line, t_treenode *ast)
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

int	is_numeric_exit(char *argv)
{
	int		i;
	char	*nb;
	char	sign;

	i = 0;
	sign = argv[0];
	if (!argv || argv[0] == '\0')
		return (0);
	if (argv[i] == '+' || argv[i] == '-')
		i++;
	if (!argv[i])
		return (0);
	while (argv[i])
	{
		if (!ft_isdigit(argv[i]))
			return (0);
		i++;
	}
	if (argv[0] == '+' || argv[0] == '-')
		nb = &argv[1];
	else
		nb = argv;
	return (compar_long_limits(nb, sign));
}

int	compar_long_limits(char *nb, char sign)
{
	char	*max;
	char	*min;

	max = "9223372036854775807";
	min = "9223372036854775808";
	if (ft_strlen(nb) > 19)
		return (0);
	if (ft_strlen(nb) == 19)
	{
		if (sign == '-')
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
	return (1);
}
