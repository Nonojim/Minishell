/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_bool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:34:40 by npederen          #+#    #+#             */
/*   Updated: 2025/06/16 14:34:40 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	is_redirection(int type)
{
	return (type == INPUT_REDIRECTION
		|| type == OUTPUT_REDIRECTION
		|| type == HERE_DOCUMENT
		|| type == APPEND_OUTPUT_REDIRECTION);
}

int	is_op_logique(int type)
{
	return (type == LOGICAL_OR
		|| type == LOGICAL_AND
		|| type == SEMICOLON
		|| type == PIPE);
}

int	is_word_type(int type)
{
	return (type == WORD
		|| type == SIMPLE_QUOTE
		|| type == DOUBLE_QUOTE
		|| type == EXPANSION);
}

int	is_bracket(int type)
{
	return (type == BRACKETS_R
		|| type == BRACKETS_L);
}
