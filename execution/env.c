/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:48:04 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/30 12:17:13 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern char	**environ;

t_env	*add_code_error(t_env	*env, int code_error)
{
	char	*value;

	value = ft_itoa(code_error);
	env = export_to_env(env, "?", value);
	free(value);
	return (env);
}

// Trouve un node existant avec cette clé
t_env	*find_node(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

// Ajoute ou modifie une variable
t_env	*export_to_env(t_env *env_list, char *key, char *value)
{
	t_env	*node;
	t_env	*new;

	node = find_node(env_list, key);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(value);
	}
	else
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (env_list);
		new->key = ft_strdup(key);
		new->value = ft_strdup(value);
		new->next = env_list;
		env_list = new;
	}
	return (env_list);
}

// Initialise depuis environ[]
t_env	*init_env_list(void)
{
	t_env	*env_list;
	char	*key;
	char	*value;
	char	*equal;
	int		i;

	i = 0;
	env_list = NULL;
	while (environ[i])
	{
		equal = ft_strchr(environ[i], '=');
		if (equal)
		{
			key = ft_substr(environ[i], 0, equal - environ[i]);
			value = ft_strdup(equal + 1);
			env_list = export_to_env(env_list, key, value);
			free(key);
			free(value);
		}
		i++;
	}
	return (env_list);
}

// Libère la liste
void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}
