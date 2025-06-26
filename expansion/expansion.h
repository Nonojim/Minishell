/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:05:55 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/25 22:21:01 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "../minishell.h"

typedef struct s_treenode t_treenode;
char	*ft_getenv(char *name, t_treenode *node);
void	expanse_ast(t_treenode *node);
char	*expand_string(char *str, t_treenode *node);
int		toggle_quote(char *str, int *i, int *in_single_quote, int *in_double_quote, char **result);
int		expand_variable(char *str, int i, char **result, t_treenode *node);
char	*clean_quote_after_expanse(char *str);

#endif
