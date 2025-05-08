/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:39:19 by npederen          #+#    #+#             */
/*   Updated: 2025/05/09 00:33:55 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "../minishell.h"

typedef struct s_treenode
{
	int					type;
	char				*str;
	struct s_treenode	*right;
	struct s_treenode	*left;
}			t_treenode;

enum e_DIRECTION
{
	LEFT,
	RIGHT,
};

#endif