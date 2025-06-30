/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:05:55 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/30 14:08:52 by lduflot          ###   ########.fr       */
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

int		toggle_quote(char *str, int *i, t_quote_state *q, char **result);
char	*expand_string(char *str, t_treenode *node);
int		expand_variable(char *str, int i, char **result, t_treenode *node);
void	expanse_ast(t_treenode *node);
char	*ft_getenv(char *name, t_treenode *node);

//a refaire:
char	*clean_quote_after_expanse(char *str);

#endif
