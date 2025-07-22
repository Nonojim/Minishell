/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:05:07 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/22 14:55:09 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../minishell.h"

// cd
int			ft_cd(t_treenode *node, t_ctx *ctx);
// echo
int			ft_echo(t_treenode *node, t_ctx *ctx);
int			ft_echo_n(char *argv);
// env
int			ft_env(t_treenode *node, t_ctx *ctx);
void		print_env_reverse(t_env *node);
//unset
int			ft_unset(t_treenode *node, t_ctx *ctx);
int			unset_head_list(t_ctx *ctx, char *key);
void		unset_list(t_ctx *ctx, char *key);
// exit
int			compar_long_limits(char *nb, char sign);
int			is_numeric_exit(char *argv);
void		error_numeric_exit(char *line, t_treenode *ast, t_ctx *ctx);
int			ft_exit(char *line, t_treenode *ast, t_ctx *ctx);
// export
int			ft_export(t_treenode *node, t_ctx *ctx);
void		print_export(t_env *env);
void		add_export_variable(t_ctx *ctx, char *arg);
void		ft_sort_env_list(t_env *env);
t_env		*copy_env(t_env *env);
void		ft_env_add_back(t_env **lst, t_env *new);
// pwd
int			ft_pwd(t_ctx *ctx);
//fish
int			ft_whale(t_treenode *node);
int			ft_shark(t_treenode *node);

#endif
