/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:05:55 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/23 12:20:24 by lduflot          ###   ########.fr       */
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
}	t_wildcard;

//expansion
void	expanse_ast(t_treenode *node, t_ctx *ctx);
void	expanse_argv(t_treenode *node, t_ctx *ctx);
void	expanse_redir(t_treenode *node, t_ctx *ctx);
void	expanse_heredoc(t_treenode *node, t_ctx *ctx);

//expansion2
char	*expand_tilde(char *str, t_ctx *ctx);
char	*expand_string(char *str, t_treenode *node, t_ctx *ctx);
char	*expand_heredoc(char	*str, t_ctx *ctx);
int		expand_variable(char *str, int i, char **result, t_ctx *ctx);

//expansion_utils
int		toggle_quote(char *str, int *i, t_quote_state *q, char **result);
char	*remove_quotes_after_expansion(const char *str);
void	add_char_to_string(char **result, char c);
char	*ft_getenv(char *name, t_ctx *ctx);

//expanse_wildcard
char	*expand_wildcard(char *str, t_treenode *node, t_ctx *ctx);
int		match_prefix(char *str, char *prefix);
int		match_middle(char *str, char **middle);
int		match_suffix(char *str, char *suffix);
char	**add_array(char **result, char *file);
void	create_prefix_middle_suffix(char *str, t_wildcard *psm);
int		create_prefix(char *str, t_wildcard *psm);
void	allocation_psm_middle(t_wildcard *psm, int middle_wildcard);
void	create_psm_middle_suffix(char *str, t_wildcard *psm, int i);
int		ft_strnstr_for_wildcard(char *str,	char **middle, int len_str);
int		count_middle_wildcard(char *str);
void	free_wildcard(t_wildcard *psm, char **result, t_treenode *node);

#endif
