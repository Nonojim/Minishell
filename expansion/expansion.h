/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:05:55 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/05 00:17:46 by npederen         ###   ########.fr       */
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

char	*expand_tilde(char *str, t_treenode *node);
void	add_char_to_string(char **result, char c);
char	*remove_quotes_after_expansion(const char *str);
int		toggle_quote(char *str, int *i, t_quote_state *q, char **result);
char	*expand_string(char *str, t_treenode *node);
int		expand_variable(char *str, int i, char **result, t_treenode *node);
void	expanse_ast(t_treenode *node);
char	*ft_getenv(char *name, t_treenode *node);

//a refaire:
char	*clean_quote_after_expanse(char *str);
//expanse_wildcard
char	*expand_wildcard(char *str);
char	*create_middle(char **middle, char *str);
void	create_prefix_and_suffix(char **prefix, char **suffix, char *str);
int		ft_strnstr_for_wildcard(char *str,	char *middle, int len_str);
int		match_middle(char *str, char *middle);
int		match_prefix(char *str, char *prefix);
int		match_suffix(char *str, char *suffix);
char	*add_string(char *result, char *file);

#endif
