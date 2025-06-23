/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:05:41 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/23 20:44:45 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

// on parcours l'ast récursivement, et on expanse avec expand_string
void	expanse_ast(t_treenode *node)
{
	int		i;
	char	*new_arg;

	if (!node)
		return ;
	if (node->argv)
	{
		i = 0;
		while (node->argv[i])
		{
			new_arg = expand_string(node->argv[i]); //expanse var
			free(node->argv[i]);
			node->argv[i] = new_arg; //remplacement
			i++;
		}
	}
	//récursivité pour allo tous les nodes
	expanse_ast(node->left);
	expanse_ast(node->right);
}

//Remplace input par les valeurs des var
char	*expand_string(char *str)
{
	char	*result;
	int		i;
	int		in_single_quote;
	int		in_double_quote;
	char	*new_str;
	char	*tmp;

	result = ft_strdup(""); //initialisation chaine result
	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	
	while (str[i])
	{
		if (toggle_quote(str, &i, &in_single_quote, &in_double_quote, &result))
			continue ;
		if (!in_single_quote && str[i] == '$' && ft_isalpha(str[i + 1]))
		{
			i = expand_variable(str, i, &result);
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

int	expand_variable(char *str, int i, char **result)
{
	int		j;
	char	*new_str;
	char	*expanse;
	char	*tmp;

	j = i + 1;
	while (str[j] != '\0' && ft_isalpha(str[j])) //on récupére toute la chaine 
		j++;
	new_str = ft_substr(str, i + 1, j - (i + 1)); //extrait nom var sans le $
	expanse = get_env_var(new_str); //récup de la value (si elle existe sinon on renvoie une chaine alloué vide, pour éviter le double free par la suite)
	free(new_str);
	tmp = *result;
	*result = ft_strjoin(tmp, expanse);
	free(tmp);
	free(expanse);
	return (j);
	//return j, pour mettre à jour y dans expanse string et pas perdre l'index
}

/*
Getenv = retourne un pointeur vers la valeur de la variable d'env name 
*/
char	*get_env_var(char *name)
{
	char	*value;

	value = getenv(name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}
