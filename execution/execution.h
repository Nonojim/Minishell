/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:14:13 by npederen          #+#    #+#             */
/*   Updated: 2025/06/26 17:11:13 by lduflot          ###   ########.fr       */
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

//Exe
int execute_node(t_treenode *node, t_token *token, char *line);

void execute_tree(t_treenode *tree, t_token *token, char *line);

//Exe_Simple_Command
int execute_simple_command(t_treenode *node, t_token *token, char *line);
char	*find_cmd_path(char *cmd, t_env *env_list);

void	free_split(char	**split);

//Exe_Pipe
int execute_pipeline(t_treenode *node, t_token *token, char *line);

//Exe_Subshell
//Exe_HereDoc
int execute_heredoc_node(t_treenode *node, t_token *token, char *line);

//Exe_Redirection
int execute_redirection_chain(t_treenode *node, t_token *token, char *line);

//ENV
int execute_subshell_node(t_treenode *node, t_token *token, char *line);



//env
t_env	*init_env_list(void);
t_env	*export_to_env(t_env *env_list, char *key, char *value);
t_env	*find_node(t_env *env, const char *key);
t_env	*add_code_error(t_env	*env, int code_error);
void	free_env_list(t_env *env);
t_env	*add_code_error(t_env	*env, int code_error);

#endif
