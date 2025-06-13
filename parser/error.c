/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:36:05 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/13 11:31:34 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
int	parse_error(int state)
{
	static int	error = 0;

	//printf("début: %i\n", error);
	if (state == -1) //lecture
		return (error);
	if (state == 0) // nouveau prompt;
		error = 0;
	else if (state == 1) //erreur rencontrer; 
	{
		//printf("ERREUR VU \n");
		error = 1;
	}
	//printf("fin : %i\n", error);
	return (error);
}

void	print_error(t_token *tokens)
{
	if (parse_error(-1))
		return ;
	if (tokens == NULL)
	{
		//printf("minishell: syntax error near unexpected token `newline'\n");
		//parse_error(1);
		return ;
	}
	parse_error(1);
	if (is_op_logique(tokens->type))
		printf("minishell: syntax error near unexpected token '%s'\n", tokens->str);
	if (is_redirection(tokens->type))
		printf("minishell: syntax error near unexpected token `newline'\n");
	if(is_bracket(tokens->type))
		printf("minishell: syntax error near unexpected token '%s'\n", tokens->str);
}

//ne fonctionne plus au second prompt, il faut réniatialiser la variable statique
// il faut penser que quand on met un " || " l'arbre doit continuer à se crée pour la suite du || !!!!!!
// cette fonction ne fonctionnera pas quand il y a une redirection > txt etc renverra une erreur
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

/*void	print_error(t_token **tokens)
{
	if ((*tokens)->type == LOGICAL_OR || (*tokens)->type == LOGICAL_AND || (*tokens)->type == SEMICOLON || (*tokens)->type == PIPE)
		printf("minishell: syntax error near unexpected token '%s'\n", (*tokens)->str);
//	else if ((*tokens)->type == BRACKETS_L || (*tokens)->type == BRACKETS_R )
//		printf("minishell: syntax error near unexpected token '%s'\n", (*tokens)->str);
	//else if ((*tokens)->type == INPUT_REDIRECTION || (*tokens)->type == OUTPUT_REDIRECTION || (*tokens)->type == HERE_DOCUMENT || (*tokens)->type == APPEND_OUTPUT_REDIRECTION)
		//printf("bash: syntax error near unexpected token `newline'\n");
}*/
