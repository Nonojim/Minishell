/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brouillon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:02:29 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/30 13:44:42 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//t_treenode	*create_branch_words(t_token **tokens)
//{
//	t_treenode	*root = NULL;
//	t_treenode	*current = NULL;
//	t_treenode	*new_node = NULL;
//
//	while (*tokens != NULL
//		&& ((*tokens)->type == WORD
//	|| (*tokens)->type == EXPANSION
//	|| (*tokens)->type == SIMPLE_QUOTE
//	|| (*tokens)->type == DOUBLE_QUOTE ))
//	{
//		new_node = create_treenode((*tokens)->type, (*tokens)->str);
//		if (!new_node || !new_node->str)
//		{
//			free_treenode(root);
//			return (NULL);
//		}
//		if (!root)
//		{
//			root = new_node;
//			current = root;
//		}
//		else
//		{
//			add_node(current, new_node, LEFT);
//			current = new_node;
//		}
//		*tokens = (*tokens)->next;
//	}
//	return (root);
//}

//Ajout traitement des tokens variable $
		/*	if (line[i] == '$')
			{
				start = i;
				//i++;
				if (line[i + 1] && ft_istokenword(line[i + 1]) == 1)
				{
					start = i;
					while(ft_istokenword(line[i]) && line[i]
					&& !is_operator_logical(line[i]))
						i++;
					str = ft_substr(line, start, i - start);
					type = type_token(str);
					add_token_end(&token, create_token(type, str));
				}
				else
				{
					i++;
					str = ft_substr(line, start, 1);
					type = type_token(str);
					add_token_end(&token, create_token(type, str));
				}
			}*/

			//// Fonction test pour le parsing si c'est une simple 
///command exemple = echo hello
//// Dans la grammaire simple command peut être couplé
///au redirection non mis dans la fonction pour l'instant
//t_treenode	*parse_simple_command_without_redirection
//(t_token **token, t_treenode *parent_node, int dir)
//{
//	t_treenode *simple_command_node = NULL;
//	
//	if ((*token)->type == WORD)
//	{
//		if (parent_node == NULL) //if is the first node;
//		{
//			simple_command_node = create_treenode(WORD, (*token)->str);
//			printf("node créer the first\n");
//			print_ast(simple_command_node, 0);
//		}
//		if (parent_node != NULL)
//		{
//			add_node(parent_node, simple_command_node, dir);
//			printf("node child créer\n");
//		}
//		//printf("node créer\n");
//		print_ast(simple_command_node, 1);
//		*token = (*token)->next;
//	}
//	return(simple_command_node);
//}

//// Print AST - NON FONCTIONNEL - A TRAVAILLER
//void	print_ast(t_treenode *node, int dir)
//{
////	while(node)
//	//{
//		if (node->left && dir == 0)
//		{
//			printf("/");
//			printf("[%d : %s]\n", node->type, node->str);
//			node = node->left;
//		}
//		if (node->right && dir == 1)
//		{
//			printf("\\");
//			printf("[%d : %s]\n", node->type, node->str);
//			node = node->right;
//		}
//	//}
//}
//				ADAPTATION DU CODE JAVA
/*t_ast *parse_command_line(t_token **tokens) {
    return parse_pipeline(tokens);
}
t_ast *parse_pipeline(t_token **tokens) {
    t_ast *left = parse_command(tokens);

    while (*tokens && (*tokens)->type == TOKEN_PIPE) {
        *tokens = (*tokens)->next;  // skip the pipe

        t_ast *right = parse_command(tokens);
        t_ast *pipe_node = malloc(sizeof(t_ast));
        pipe_node->type = NODE_PIPE;
        pipe_node->left = left;
        pipe_node->right = right;
        pipe_node->args = NULL;

        left = pipe_node;
    }
    return left;
}
#include <stdlib.h>

t_ast *parse_command(t_token **tokens) {
    if (!*tokens || (*tokens)->type != TOKEN_WORD)
        return NULL;

    int argc = 0;
    t_token *start = *tokens;

    while (*tokens && (*tokens)->type == TOKEN_WORD) {
        argc++;
        *tokens = (*tokens)->next;
    }

    char **args = malloc(sizeof(char *) * (argc + 1));
    for (int i = 0; i < argc; i++) {
        args[i] = start->str;
        start = start->next;
    }
    args[argc] = NULL;

    t_ast *cmd = malloc(sizeof(t_ast));
    cmd->type = NODE_COMMAND;
    cmd->left = NULL;
    cmd->right = NULL;
    cmd->args = args;

    return cmd;
}

// V1 AST 
/*t_treenode	*create_tree(t_token *token_list)
{
	t_treenode	*root = NULL;
	t_treenode	*left_node = NULL;
	t_treenode	*right_node = NULL;
	t_treenode	*op_node = NULL;
	
//	t_treenode *relie_branche = NULL;

	if (token_list && token_list->type == WORD)
		left_node = create_branch_words(&token_list);
	root = left_node;
	if (token_list && token_list->type != WORD)
	{
		op_node = create_treenode(token_list->type, token_list->str);
		add_node(op_node, root, LEFT);
		root = op_node;
		token_list = token_list->next;
	}
	if (token_list && token_list->type == WORD)
	{
		right_node = create_branch_words(&token_list);
		add_node(op_node, right_node, RIGHT);
	}
	if (token_list)
	{
		create_tree(token_list);
		//relie_branche = create_tree(token_list);
		//add_node(relie_branche, root, LEFT);
	}
	if (token_list && token_list->type != WORD)
	{
		op_node = create_treenode(token_list->type, token_list->str);
		add_node(op_node, root, LEFT);
		root = op_node;
		token_list = token_list->next;
	}
	if (token_list && token_list->type == WORD)
	{
		right_node = create_branch_words(&token_list);
		add_node(op_node, right_node, RIGHT);
	}
	return (root);
}*/
