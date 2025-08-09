/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:05:55 by lduflot           #+#    #+#             */
/*   Updated: 2025/08/09 17:49:56 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "../minishell.h"

typedef struct s_quote_state
{
	int	in_single_quote;
	int	in_double_quote;
}	t_quote_state;

typedef struct s_wildcard
{
	char	*prefix;
	char	**middle;
	char	*suffix;
	int		wildcard_index;
	int		len_argv;
	int		len_result;
}	t_wildcard;

//expansion
void		expanse_ast(t_treenode *node, t_ctx *ctx);
void		expanse_argv(t_treenode *node, t_ctx *ctx);
void		expanse_redir(t_treenode *node, t_ctx *ctx);
void		expanse_heredoc(t_treenode *node, t_ctx *ctx);
void		delete_var_empty(t_treenode *node);
int			verif_quote_only(t_treenode *node);

//expansion2
char		*expand_tilde(char *str, t_ctx *ctx);
char		*expand_string(char *str, t_treenode *node, t_ctx *ctx,\
	int wildcard_index);
char		*shearch_and_add_var(char *str, char *result, t_ctx *ctx);
char		*expand_heredoc(char	*str, t_ctx *ctx);
int			expand_variable(char *str, int i, char **result, t_ctx *ctx);

//expansion3
int			var_with_quote_after_dollar(int *j, char **result, char *str,\
		int *i);
int			var_with_number_after_dollar(int *j, char *str, int *i);

//expansion_utils
int			toggle_quote(char *str, int *i, t_quote_state *q, char **result);
char		*remove_quotes_after_expansion(const char *str);
void		add_char_to_string(char **result, char c);
char		*ft_getenv(char *name, t_ctx *ctx);

//expanse_wildcard

// wildcard_psm
t_wildcard	*init_struct_psm(int wildcard_index);
int			match_prefix(char *str, char *prefix);
int			match_middle(char *str, char **middle);
int			match_suffix(char *str, char *suffix);
char		**add_array(char **result, char *file);
void		create_prefix_middle_suffix(char *str, t_wildcard *psm);
int			create_prefix(char *str, t_wildcard *psm);
void		allocation_psm_middle(t_wildcard *psm, int middle_wildcard);
void		create_psm_middle_suffix(char *str, t_wildcard *psm, int i);
int			count_middle_wildcard(char *str);
void		sort_argv(char **array);
void		free_expand_variable(char *tmp, char *expanse, char *new_str);

//wildcard_shearch
int			ft_strnstr_for_wildcard(char *str,	char **middle, int len_str);
void		free_wildcard(t_wildcard *psm, char **result, t_treenode *node);
void		wildcard_redir(char **result, t_ctx *ctx, t_wildcard *psm,\
											t_treenode *node);
char		*result_wildcard(char **result, t_treenode *node, t_ctx *ctx,\
											t_wildcard *psm);
char		*expand_wildcard(char *str, t_treenode *node, t_ctx *ctx,\
											int wildcard_index);
char		**found_match(DIR *dir, t_wildcard *psm, char **result);
//wildcard_new_argv
void		create_new_argv(char **result, t_treenode *node,\
											t_wildcard *idx);
char		**build_new_argv(t_treenode *node, char **result, t_wildcard *idx,\
												char **new_argv);
int			len_array(char **result);

#endif
