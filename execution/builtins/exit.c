/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:25:50 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/22 14:49:13 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
	* exit [n]
	* Si n == NULL quitte avec code actuel $?
	* Si n == non num = numeric argument required exit : 2
	* Si n + 1 != NULL = too many arguments ne quitte pas return 1
code_error = ft_atoi(ast->argv[1]) % 256; 
//quand on fait exit 1000 error = 232 donc 1000 % 256. 
Le code de sortie étant limité à 8 bits = 255 max. 
Bash fait un modulo de 256 pour avoir un affichage correct. 
*/

int	ft_exit(char *line, t_treenode *ast, t_ctx *ctx)
{
	printf("exit\n");
	if (ast->argv[1])
	{
		if (!is_numeric_exit(ast->argv[1]))
			error_numeric_exit(line, ast, ctx);
		else if (ast->argv[2])
		{
			ft_fprintf(2, "Minishell: exit: too many arguments\n");
			ctx->exit_code = 1;
			return (1);
		}
		else
			ctx->exit_code = ft_atoi(ast->argv[1]) % 256;
	}
	else
		ctx->exit_code = 0;
	free(line);
	free_env_list(ctx->env);
	free_treenode(ast);
	rl_clear_history();
	exit(ctx->exit_code);
}

void	error_numeric_exit(char *line, t_treenode *ast, t_ctx *ctx)
{
	printf("exit\n");
	ft_fprintf(2, "Minishell: exit: %s: numeric argument required\n", \
						ast->argv[1]);
	free(line);
	free_env_list(ctx->env);
	free_treenode(ast);
	rl_clear_history();
	exit(2);
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
