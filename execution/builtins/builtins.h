/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:05:07 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/30 11:59:48 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../minishell.h"

// cd
int		ft_cd(t_treenode *node);
// echo
int		ft_echo(t_treenode *node);
int		ft_echo_n(char *argv);
// env
int		ft_env(t_env *env_list);
//unset
int		ft_unset(t_treenode *node);
int		unset_head_list(t_treenode *node, char *key);
void	unset_list(t_treenode *node, char *key);
// exit
int		compar_long_limits(char *nb, char sign);
int		is_numeric_exit(char *argv);
void	error_numeric_exit(t_token *token, char *line, t_treenode *ast);
int		ft_exit(char *line, t_token *token, t_treenode *ast);
// export
int		ft_export(t_treenode *node);
void	print_export(t_env *env);
void	add_export_variable(t_treenode *node, char *arg);
// pwd
int		ft_pwd(t_treenode *node);

#endif
