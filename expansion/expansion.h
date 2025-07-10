/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:05:55 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/07 23:50:05 by lduflot          ###   ########.fr       */
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


typedef struct	s_wildcard
{
	char	*prefix;
	char	*middle;
	char	*suffix;
}	t_wildcard;


char	*expand_tilde(char *str, t_ctx *ctx);
void	add_char_to_string(char **result, char c);
char	*remove_quotes_after_expansion(const char *str);
int		toggle_quote(char *str, int *i, t_quote_state *q, char **result);
char	*expand_string(char *str, t_treenode *node, t_ctx *ctx);
int		expand_variable(char *str, int i, char **result, t_ctx *ctx);
void	expanse_ast(t_treenode *node, t_ctx *ctx);
//void	give_env(t_treenode *node);
char	*ft_getenv(char *name, t_ctx *ctx);

//a refaire:
char	*clean_quote_after_expanse(char *str);
//expanse_wildcard
char	*expand_wildcard(char *str, t_treenode *node);
int	match_prefix(char *str, char *prefix);
int	match_middle(char *str, char *middle);
int	match_suffix(char *str, char *suffix);
char	**add_array(char **result, char *file);
void	create_prefix_middle_suffix(char *str, t_wildcard *psm);

#endif
