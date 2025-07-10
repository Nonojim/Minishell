/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:48:03 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/09 16:06:54 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

//Fichier à retirer du MakeFile à la fin du projet
void	print_indent(int depth)
{
	while (depth-- > 0)
		printf("  ");
}

void	astreeprint(t_treenode *node, int depth)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	print_indent(depth);
	printf("[Type: %i", node->type);
	if (node->str)
		printf(", data: \"%s\"]", node->str);
	if (node->argv)
	{
		printf(", argv: [");
		i = 0;
		while (node->argv[i])
		{
			printf("%s", node->argv[i]);
			if (node->argv[i + 1])
				printf(", ");
			i++;
		}
		printf("]");
	}
	printf("\n");
	if (node->left)
	{
		print_indent(depth);
		printf("Left:\n");
		astreeprint(node->left, depth + 1);
	}
	if (node->right)
	{
		print_indent(depth);
		printf("Right:\n");
		astreeprint(node->right, depth + 1);
	}
}
