/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:48:04 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/08 14:07:52 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern char	**environ;

/*void	add_code_error(t_env	**env, int code_error)
{
	char	*value;
	
	(void)env;
	value = ft_itoa(code_error);
	export_to_env(env, "?", value);
	free(value);
}*/

/*void	add_code_error(t_ctx exit_code, int code_error)
{
	ctw->exit_code = code_error;
}*/
//dans l'expansion : 
//return(ft_itoa(ctx->exit_code));

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
	t_env	*new;
	t_env	*tmp;

	node = find_usrvar(*env_list, key);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(value);
	}
	else
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return ;
		new->key = ft_strdup(key);
		new->value = ft_strdup(value);
		new->next = NULL;
		if (!*env_list)
		{
			*env_list = new;
			return;
		}
		tmp = *env_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
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
			export_to_env(&env_list, key, value);
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
	int	count = 0;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		count++;
	}
	//printf("free_env_list: %d variables libérées\n", count);
}
