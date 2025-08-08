/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:14:13 by npederen          #+#    #+#             */
/*   Updated: 2025/08/08 17:24:48 by lduflot          ###   ########.fr       */
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

typedef struct s_ctx
{
	t_env		*env;
	char		**envp;
	int			exit_code;
	t_token		*head_token_list;
	t_treenode	*root;
}	t_ctx;

//list to char**
char		**list_to_dynamiccarray(t_ctx *ctx);

// Exe
int			execute_node(t_treenode *node, char *line, t_ctx *ctx);
int			execute_node_simple(t_treenode *node, char *line, t_ctx *ctx);
int			execute_node_logical(t_treenode *node, char *line, t_ctx *ctx);
int			execute_node_redir(t_treenode *node, char *line, t_ctx *ctx);
void		execute_tree(t_treenode *tree, char *line, t_ctx *ctx);

// Exe_Simple_Command
int			is_builtin(char *cmd);
int			execute_simple_command(t_treenode *node, char *line, t_ctx *ctx);
int			execute_external_command(t_treenode *node, t_ctx *ctx, char *line);
int			execute_builtin_command(t_treenode *node, char *line, t_ctx *ctx);
int			external_command_status(t_ctx *ctx, pid_t pid);
char		*find_cmd_path(char *cmd, t_env *env_list);
void		free_split(char **split);
char		**list_to_dynamiccarray(t_ctx *ctx);
void		add_value(t_env *tmp, char *key_eq, char **array, int *i);
int			count_env(t_env *env);
void		free_execve(t_treenode *node, char *line, t_ctx *ctx,\
	char *cmd_path);
void		handle_child_process(t_treenode *node, t_ctx *ctx,\
	char *line, char *cmd);
char		*shearch_cmd_path(char *cmd, t_ctx *ctx,\
	char *line, t_treenode *node);

// Exe_Pipe
int			execute_pipeline(t_treenode *node, char *line, t_ctx *ctx);
int			pipe_status(pid_t pid1, pid_t pid2, t_ctx *ctx);
void		pipe_left(t_treenode *node, char *line, int pipefd[2], t_ctx *ctx);
void		pipe_right(t_treenode *node, char *line, int pipefd[2], t_ctx *ctx);

// Exe_Subshell
int			execute_subshell_node(t_treenode *node, char *line, t_ctx *ctx);
int			subshell_status(t_ctx *ctx, pid_t pid);

// Exe_HereDoc
int			execute_heredoc_node(t_treenode *node, char *line, t_ctx *ctx);
int			heredoc_status(t_ctx *ctx, pid_t pid, t_treenode *node, char *line);
void		free_hd(t_treenode *node, t_ctx *ctx, char *line);
int			found_last_heredoc_and_cmd(t_treenode *node, t_treenode **last_hd,\
				t_treenode **cmd, t_ctx *ctx);

// Exe_Redirection
char		**copy_argv_in_newcmd(char **argv);
int			create_and_exe_cmd(char **tmp_argv, char *line, t_ctx *ctx);
char		**create_new_node_arg(int *len_res, int *len_cur,\
					char **result, char **curent);
char		**recup_all_argv_without_cmd(t_treenode *node);
int			redir_heredoc(t_treenode *node, t_ctx *ctx);
int			execute_redirection_chain(t_treenode *node, char *line, t_ctx *ctx);
int			redir_input(t_treenode *node, t_ctx *ctx);
int			redir_output(t_treenode *node, t_ctx *ctx);
int			redir_append(t_treenode *node, t_ctx *ctx);
int			apply_redirections(t_treenode *node, char *line, t_ctx *ctx);
void		dup_and_close(int saved_stdin, int saved_stdout);
void		new_argv_cmd(t_treenode *redir_node);
char		**create_new_array_cmd(t_treenode *redir_node, t_treenode *cmd);
void		create_new_argv_cmd(char **new_argv, int *i, t_treenode *node);
t_treenode	*find_command_node(t_treenode *node);

// Env
t_env		*init_env_list(void);
void		change_shlvl(t_env	**env);
void		export_to_env(t_env **env_list, char *key, char *value);
t_env		*find_usrvar(t_env *env, const char *key);
void		free_env_list(t_env *env);
void		add_new_var(t_env **env_list, char *key, char *value);
void		create_env_list_with_environ(t_env **env_list);

#endif
