/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:48:04 by lduflot           #+#    #+#             */
/*   Updated: 2025/08/02 13:02:34 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern char	**environ;

// Trouve un node existant avec cette clé
t_env	*find_usrvar(t_env *env, const char *key)
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
void	export_to_env(t_env **env_list, char *key, char *value)
{
	t_env	*node;

	node = find_usrvar(*env_list, key);
	if (node)
	{
		if (value)
		{
			if (node->value)
				free(node->value);
			node->value = ft_strdup(value);
		}
	}
	else
		add_new_var(env_list, key, value);
}

// Initialise depuis environ[]
t_env	*init_env_list(void)
{
	t_env	*env_list;

	env_list = NULL;
	create_env_list_with_environ(&env_list);
	change_shlvl(&env_list);
	if (find_usrvar(env_list, "PWD") == NULL)
		export_to_env(&env_list, "PWD", getcwd(NULL, 0));
	if (find_usrvar(env_list, "PATH") == NULL)
	{
		ft_fprintf(1, "No PATH found a standard unix PATH will be exported\n");
		export_to_env(&env_list, \
		"PATH", "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	}
	return (env_list);
}

void	create_env_list_with_environ(t_env **env_list)
{
	char	*key;
	char	*value;
	char	*equal;
	int		i;

	i = 0;
	while (environ[i])
	{
		equal = ft_strchr(environ[i], '=');
		if (equal)
		{
			key = ft_substr(environ[i], 0, equal - environ[i]);
			value = ft_strdup(equal + 1);
		}
		else
		{
			key = ft_strdup(environ[i]);
			value = NULL;
		}
		export_to_env(env_list, key, value);
		free(key);
		free(value);
		i++;
	}
}

// Libère la liste
void	free_env_list(t_env *env)
{
	t_env	*tmp;
	int		count;

	count = 0;
	while (env)
	{
		tmp = env;
		env = env->next;
		free_then_setnull((void **)&tmp->key);
		if (tmp->value)
			free_then_setnull((void **)&tmp->value);
		free_then_setnull((void **)&tmp);
		count++;
	}
}
