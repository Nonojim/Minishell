/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:14:13 by npederen          #+#    #+#             */
/*   Updated: 2025/06/25 11:04:20 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"

typedef struct s_env
{
	char *key; // ex: "USER"
	char *value; // ex"nm de l'useur"
	struct s_env *next;
}	t_env;


typedef struct s_treenode t_treenode;
 
int		execute_redirection_chain(t_treenode *node);
int		execute_heredoc_node(t_treenode *node);
int		execute_pipeline(t_treenode *node);
int		execute_subshell_node(t_treenode *node);
int		execute_simple_command(t_treenode *node);
int		execute_node(t_treenode *node);
void	execute_tree(t_treenode *tree);

//env
t_env	*init_env_list(void);
t_env	*export_to_env(t_env *env_list, char *key, char *value);
t_env	*find_node(t_env *env, const char *key);
void	free_env_list(t_env *env);

#endif
