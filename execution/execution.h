/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:14:13 by npederen          #+#    #+#             */
/*   Updated: 2025/07/05 16:57:21 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// Exe
int		execute_node(t_treenode *node, t_token *token, char *line);
int		execute_node_simple(t_treenode *node, t_token *token, char *line);
int		execute_node_logical(t_treenode *node, t_token *token, char *line);
int		execute_node_redir(t_treenode *node, t_token *token, char *line);
void	execute_tree(t_treenode *tree, t_token *token, char *line);

// Exe_Simple_Command
int		is_builtin(char *cmd);
int		execute_simple_command(t_treenode *node, t_token *token, char *line);
int		execute_external_command(t_treenode *node);
int		execute_builtin_command(t_treenode *node, t_token *token, char *line);
int		external_command_status(t_treenode *node, pid_t pid);
char	*find_cmd_path(char *cmd, t_env *env_list);
void	free_split(char **split);

// Exe_Pipe
int		execute_pipeline(t_treenode *node, t_token *token, char *line);
int		pipe_status(t_treenode *node, pid_t pid1, pid_t pid2);
void	pipe_left(t_treenode *node, t_token *token, char *line, int pipefd[2]);
void	pipe_right(t_treenode *node, t_token *token, char *line, int pipefd[2]);

// Exe_Subshell
int		execute_subshell_node(t_treenode *node, t_token *token, char *line);
int		subshell_status(t_treenode *node, pid_t pid);

// Exe_HereDoc
int		execute_heredoc_node(t_treenode *node, t_token *token, char *line);
int		heredoc_status(t_treenode *node, pid_t pid);

// Exe_Redirection
int		execute_redirection_chain(t_treenode *node, t_token *token, char *line);
int		redir_input(t_treenode *node, t_token *token, char *line);
int		redir_output(t_treenode *node, t_token *token, char *line);
int		redir_append(t_treenode *node, t_token *token, char *line);

// Env
t_env	*init_env_list(void);
void	export_to_env(t_env **env_list, char *key, char *value);
t_env	*find_node(t_env *env, const char *key);
void	add_code_error(t_env **env, int code_error);
void	free_env_list(t_env *env);

#endif
