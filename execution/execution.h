/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:14:13 by npederen          #+#    #+#             */
/*   Updated: 2025/06/20 23:34:14 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"

typedef struct s_treenode t_treenode;
 
int		execute_redirection_chain(t_treenode *node);
int		execute_heredoc_node(t_treenode *node);
int		execute_pipeline(t_treenode *node);
int		execute_subshell_node(t_treenode *node);
int		execute_simple_command(t_treenode *node);
int		execute_node(t_treenode *node);
void	execute_tree(t_treenode *tree);

#endif
