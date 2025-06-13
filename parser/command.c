/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:29:59 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/13 11:29:58 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_command_node(t_token **tokens);
t_treenode	*parse_command_node1(t_token **tokens);
t_treenode	*parse_command_node2(t_token **tokens);

/*
<command>     ::= "(" <line> ")" | <simple_command>
							|	"(" <line> ")" 
							| "(" <line> ")" redirection
							|	<simple_command>
*/

t_treenode	*parse_command_node(t_token **tokens)
{
	t_token		*tmp;
	t_treenode	*node;

	tmp = *tokens;
	node = NULL;
	if (parse_error(-1) == 1)
			return (NULL);
	node = parse_command_node1(tokens);
	if (parse_error(-1))
			return (NULL);
	if (node)
		return (node);
	*tokens = tmp;
	node = parse_command_node2(tokens);
	if (parse_error(-1) == 1)
		return (NULL);
	if (node)
		return (node);
	*tokens = tmp;
	return(NULL);
}

// "(" <line> ")" redirection
t_treenode	*parse_command_node1(t_token **tokens)
{
	t_token		*tmp = *tokens;
	t_treenode	*line_node; //contenu du sous_shell
	t_treenode	*subshell_node;
	t_treenode	*redir_node; //stock redirection trouver aprés parenthese

	if (*tokens == NULL || (*tokens)->type != BRACKETS_L)
		return (NULL);
	*tokens = (*tokens)->next; // on mange la bracket_L 
	line_node = parse_line_node(tokens); // parse int subshell
	if (line_node == NULL || *tokens == NULL || (*tokens)->type != BRACKETS_R)
	{
		print_error(*tokens); // PB ON ENVOIE PAS BRACKET_R IL FAUT TROUVER UNE ALTERNATIVE !!
		free_treenode(line_node);
		*tokens = tmp;
		return (NULL);
	}
	*tokens = (*tokens)->next; // on mange bracket_R
	subshell_node = create_treenode(SUBSHELL, "()");
	subshell_node->left = line_node; //contient commande subshell	
	tmp = *tokens;
//	printf("%p\n", (*tokens)->str);
	if (line_node->type == SUBSHELL && line_node->left && line_node->left->argv[1] == NULL /*&& node->left->left && node->left->left->argv[1] == NULL*/)
  {
		print_error(*tokens); // MEME ERREUR QUE EN HAUT 
  	free_treenode(subshell_node);
			//printf("minishell: syntax error near unexpected token ')'\n");
     //*tokens = NULL;
    return (NULL);
  }
	while ((redir_node = parse_redirection_node(tokens)) != NULL)
	{
		redir_node->left = subshell_node;
		subshell_node = redir_node;
	}
	return (subshell_node);
}

//simple_command
t_treenode	*parse_command_node2(t_token **tokens)
{
	t_treenode	*simple_cmd_node;

	simple_cmd_node  = parse_simple_command_node(tokens);
	return (simple_cmd_node);

}
