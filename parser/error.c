/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:36:05 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/17 14:29:55 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/*
	* State :
* -1 = lecture dans les bloc parsing pour vérifier l'état de l'erreur
*  0 = on remet à zéro la static (nouveau prompt)
*  1 = erreur détecté 
	*/
int	parse_error(int state)
{
	static int	error = 0;

	if (state == -1)
		return (error);
	if (state == 0)
		error = 0;
	else if (state == 1)
		error = 1;
	return (error);
}

void	print_error(t_token *tokens)
{
	if (parse_error(-1))
		return ;
	if (tokens == NULL)
	{
		parse_error(1);
		printf("minishell: syntax error near unexpected token `newline'\n");
		return ;
	}
	parse_error(1);
	if (is_op_logique(tokens->type) || is_word_type(tokens->type))
		printf("minishell: syntax error near unexpected token '%s'\n",
			tokens->str);
	if (is_redirection(tokens->type) && tokens->next != NULL
		&& is_redirection(tokens->next->type))
	{
		printf("minishell: syntax error near unexpected token '%s'\n",
			tokens->next->str);
		return ;
	}
	if (is_redirection(tokens->type))
		printf("minishell: syntax error near unexpected token `newline'\n");
	if (is_bracket(tokens->type))
		printf("minishell: syntax error near unexpected token '%s'\n",
			tokens->str);
}

t_treenode	*printerror_then_return_null(t_token **tokens)
{
	print_error(*tokens);
	return (NULL);
}

t_treenode	*printerror_free_return_null(t_token **tokens, t_treenode *node)
{
	print_error(*tokens);
	return (free_then_return_null(node));
}

int	parse_cmd(char *cmd, int *error)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (0);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (0);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (0);
	else if (ft_strcmp(cmd, "export") == 0)
		return (0);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (0);
	else if (ft_strcmp(cmd, "env") == 0)
		return (0);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (0);
	else if (ft_strcmp(cmd, "test") == 0)
		return (0);
	else if (*error == 0)
	{
		printf("%s: command not found\n", cmd);
		*error = 1;
		return (1);
	}
	return (1);
}
