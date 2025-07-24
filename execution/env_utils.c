/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:49:22 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/24 16:50:18 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	add_new_var(t_env **env_list, char *key, char *value)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	ft_memset(new, 0, sizeof(t_env));
	if (key)
		new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	if (!*env_list)
	{
		*env_list = new;
		return ;
	}
	tmp = *env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	change_shlvl(t_env	**env)
{
	t_env	*shlvl;
	char	*new_shlvl;
	int		i;

	shlvl = find_usrvar(*env, "SHLVL");
	if (!shlvl)
		i = 0;
	else
		i = ft_atoi(shlvl->value);
	new_shlvl = ft_itoa(i + 1);
	export_to_env(env, "SHLVL", new_shlvl);
	free(new_shlvl);
}
