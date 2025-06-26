/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:05:41 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/26 11:41:06 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"


/*
Refactor fonction getenv, car getenv ne check que dans levrai shell pas dans l'env de mon minishell qui manipule une copie interne !
Quand je faisais export et echo par la suite renvoyé $var global et pas celle de mon t_env.

*/
char	*ft_getenv(char *name, t_treenode *node)
{
	t_env	*node_env = find_node(node->env, name); //on cherche si la variable d'env existe dans t_env
	if (!node_env)
		return (ft_strdup("")); //return(NULL); ->segfault
	return (ft_strdup(node_env->value));
}
// on parcours l'ast récursivement, et on expanse avec expand_string
void	expanse_ast(t_treenode *node)
{
	int		i;
	char	*new_arg;

	if (!node)
		return ;
	//propage l'env à tous les noeuds de l'AST 
	//sinon (echo $USER && echo hello = n'affiche que hello)
	if (node->left)
		node->left->env = node->env;
	if (node->right)
		node->right->env = node->env;
	if (node->argv)
	{
		i = 0;
		while (node->argv[i])
		{
			new_arg = expand_string(node->argv[i], node); //expanse var
			free(node->argv[i]);
			node->argv[i] = new_arg; //remplacement
			i++;
		}
	}
	if (node->type == HERE_DOCUMENT)
	{
		i = 0;
		if (node->str[i] == '\'' || node->str[i] == '"') // Si delimitateur entouré de quotes on expanse par l'intérieur.
			return ;
		else
		{
			while (node->argv && node->argv[i])
			{
				new_arg = expand_string(node->argv[i], node);
				free(node->argv[i]);
				node->argv[i] = new_arg;
				i++;
			}
		}
	}
	if (node->type == WORD && node->argv && node->argv[0]) // Delete la data orginal et remplace par l'expansion/ounon.
	{
		free(node->str);
		node->str = ft_strdup(node->argv[0]);
	}
	//récursivité pour allo tous les nodes
	expanse_ast(node->left);
	expanse_ast(node->right);
}

//Remplace input par les valeurs des var
char	*expand_string(char *str, t_treenode *node)
{
	char	*result;
	int		i;
	int		in_single_quote;
	int		in_double_quote;
	char	*new_str;
	char	*tmp;
	char	*home;

	result = ft_strdup(""); //initialisation chaine result
	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (str[i])
	{
	//i = 0;
		if (toggle_quote(str, &i, &in_single_quote, &in_double_quote, &result))
			continue ;
		if (!in_single_quote && !in_double_quote && str[i] == '~') //pas d'expansion si simple/double quote !
		{
			home = ft_getenv("HOME", node);
			if (home)
			{
				new_str = ft_strdup(str + 1);
				tmp = ft_strjoin(home, new_str);
				free(new_str);
				return (tmp);
			}
		}
	if (!in_single_quote && str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?'))
		{
			i = expand_variable(str, i, &result, node);
			continue ;
		}
		//else //si pas de var d'environnement
		else
		{
			new_str = ft_substr(str, i, 1);
			tmp = result;
			result = ft_strjoin(tmp, new_str);
			free(tmp);
			free(new_str);
			i++;
		}
	}
	return (result);
}

/* Les deux premiers blocs if = TOGGLE QUOTES
			* Deux flags : double, single
			* Si on lit un ' et qu'on est pas déjà dans un double alors on ouvre ou ferme un bloc de quote simple.
			*/
int	toggle_quote(char *str, int *i, int *in_single_quote, int *in_double_quote, char **result)
{
	char	*new_str;
	char	*tmp;

	if (str[*i] == '\'' && !(*in_double_quote))
	{
		*in_single_quote = !(*in_single_quote);
		new_str = ft_substr(str, *i, 1);
		tmp = *result;
		*result = ft_strjoin(tmp, new_str);
		free(tmp);
		free(new_str);
		(*i)++;
		return (1);
	}
	if (str[*i] == '"' && !(*in_single_quote))
	{
		*in_double_quote = !(*in_double_quote);
		new_str = ft_substr(str, *i, 1);
		tmp = *result;
		*result = ft_strjoin(tmp, new_str);
		free(tmp);
		free(new_str);
		(*i)++;
		return (1);
	}
	return (0);
}

int	expand_variable(char *str, int i, char **result, t_treenode *node)
{
	int		j;
	char	*new_str;
	char	*expanse;
	char	*tmp;

	if (str[i + 1] == '?')
	{
		expanse = ft_getenv("?", node);
		if (!expanse)
			expanse = ft_strdup("0");
		tmp = *result;
		*result = ft_strjoin(tmp, expanse);
		free(tmp);
		free(expanse);
		return (i + 2); // saute $ et ? 
	}
	j = i + 1;
	while (str[j] != '\0' && (ft_isalpha(str[j]) || str[j] == '_')) //on récupére toute la chaine 
		j++;
	new_str = ft_substr(str, i + 1, j - (i + 1)); //extrait nom var sans le $
	expanse = ft_getenv(new_str, node); //récup de la value (si elle existe sinon on renvoie une chaine alloué vide, pour éviter le double free par la suite)
	free(new_str);
	tmp = *result;
	*result = ft_strjoin(tmp, expanse);
	free(tmp);
	free(expanse);
	return (j);
	//return j, pour mettre à jour y dans expanse string et pas perdre l'index
}
