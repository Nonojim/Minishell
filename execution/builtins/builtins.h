/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:05:07 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/26 07:15:02 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../minishell.h"

typedef struct s_env t_env;
// cd
// echo
int	ft_echo(t_treenode *node);
int	ft_echo_n(char *argv);

// env
//
int	ft_env(t_env *env_list);

// exit
void	ft_exit(char *line, t_token *token, t_treenode *ast);
// export
int	ft_export(t_treenode *node);
// pwd
int	ft_pwd(t_treenode *node);

#endif

/*int	parse_cmd(char *cmd, int *error)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (0);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (0);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (0);
	else if (ft_strcmp(cmd, "export") == 0)
		return (0);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (0);
	else if (ft_strcmp(cmd, "env") == 0)
		return (0);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (0);
	else if (ft_strcmp(cmd, "test") == 0)
		return (0);
	else if (*error == 0)
	{
		printf("%s: command not found\n", cmd);
		*error = 1;
		return (1);
	}
	return (1);
}*/
