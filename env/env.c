/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:49:03 by npederen          #+#    #+#             */
/*   Updated: 2025/06/21 17:49:03 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern char **environ;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}	t_env;

// Duplicate string (remplace par ta propre ft_strdup si tu veux)
char	*ft_strdup(const char *s)
{
	char *dup = malloc(strlen(s) + 1);
	if (!dup)
		return NULL;
	strcpy(dup, s);
	return dup;
}
// Substring (remplace par ta propre ft_substr si tu veux)
char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	if (!s || start >= strlen(s))
		return ft_strdup("");
	size_t maxlen = strlen(s + start);
	if (len > maxlen)
		len = maxlen;
	char *sub = malloc(len + 1);
	if (!sub)
		return NULL;
	strncpy(sub, s + start, len);
	sub[len] = '\0';
	return sub;
}
// Trouve un node existant avec cette clé
t_env *find_node(t_env *env, const char *key)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0)
			return env;
		env = env->next;
	}
	return NULL;
}
// Ajoute ou modifie une variable
t_env *export_to_env(t_env *env_list, char *key, char *value)
{
	t_env *node = find_node(env_list, key);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(value);
	}
	else
	{
		t_env *new = malloc(sizeof(t_env));
		if (!new)
			return env_list;
		new->key = ft_strdup(key);
		new->value = ft_strdup(value);
		new->next = env_list;
		env_list = new;
	}
	return env_list;
}
// Initialise depuis environ[]
t_env *init_env_list(void)
{
	t_env *env_list = NULL;
	for (int i = 0; environ[i]; i++)
	{
		char *equal = strchr(environ[i], '=');
		if (equal)
		{
			char *key = ft_substr(environ[i], 0, equal - environ[i]);
			char *value = ft_strdup(equal + 1);
			env_list = export_to_env(env_list, key, value);
			free(key);
			free(value);
		}
	}
	return env_list;
}
// Affiche la liste
void print_env(t_env *env_list)
{
	t_env *tmp = env_list;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
// Libère la liste
void free_env_list(t_env *env)
{
	t_env *tmp;
	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}
// Programme de test
int	main(void)
{
	t_env *myenv = init_env_list();

	print_env(myenv);
	free_env_list(myenv);
	return 0;
}
