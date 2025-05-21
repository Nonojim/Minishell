/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brouillon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:02:29 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/21 12:56:48 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

			//// Fonction test pour le parsing si c'est une simple command exemple = echo hello
//// Dans la grammaire simple command peut être couplé au redirection non mis dans la fonction pour l'instant
//t_treenode	*parse_simple_command_without_redirection(t_token **token, t_treenode *parent_node, int dir)
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