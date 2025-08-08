/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:05:07 by lduflot           #+#    #+#             */
/*   Updated: 2025/08/08 19:37:43 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../minishell.h"

// cd
int			ft_cd(t_treenode *node, t_ctx *ctx);
char		*cd_home_oldpwd(t_treenode *node, char *oldpwd, t_ctx *ctx);
int			cd_many_arg(char *oldpwd, t_ctx *ctx);
char		*cd_home_target(char *oldpwd, t_ctx *ctx);
char		*cd_oldpwd_target(char *oldpwd, t_ctx *ctx);
int			cd_check_empty_target(char *target, t_treenode *node,\
												char *oldpwd, t_ctx *ctx);
void		free_cd(char *oldpwd, char *target);
int			cd_access(char *target, char *oldpwd, t_ctx *ctx);
void		update_pwd(t_ctx *ctx);
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
void		free_key_value(char *key, char *value);
void		ft_sort_env_list(t_env *env);
t_env		*copy_env(t_env *env);
void		ft_env_add_back(t_env **lst, t_env *new);
// pwd
int			ft_pwd(t_ctx *ctx, t_treenode *node);
int			check_argv_pwd(t_treenode *node, t_ctx *ctx);
//fish
int			ft_whale(t_treenode *node);
int			ft_shark(t_treenode *node);

#endif
