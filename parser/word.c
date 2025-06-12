/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:30:57 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/12 20:43:24 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_word_node(t_token **tokens);
t_treenode	*parse_word1(t_token **tokens);
int	parse_cmd(char *cmd, int *error);

t_treenode *parse_word_node(t_token **tokens)
{
	int	argc = 0;
	int	i = 0;
	t_token *tmp = *tokens;
	t_treenode *cmd_node;
	char	**argv;
	static int	count = 0;

	//printf("je passe ici\n");
	//printf("%p\n", (*tokens)->str);
	while (tmp != NULL
		&& (tmp->type == WORD
	|| tmp->type == EXPANSION
	|| tmp->type == SIMPLE_QUOTE
	|| tmp->type == DOUBLE_QUOTE))
	{
		argc++;
		tmp = tmp->next;
	}
	if (argc == 0)
		return NULL;
	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return NULL;
	tmp = *tokens;
	while (i < argc)
	{
		argv[i] = ft_strdup((tmp)->str);
		tmp = tmp->next;
		i++;
	}
	argv[argc] = NULL;
	cmd_node = create_treenode(0, argv[0]);
	cmd_node->argv = argv;
	*tokens = tmp;
	count++;
//	printf("-%i-", count);
	return (cmd_node);
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
