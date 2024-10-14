/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:09:29 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/14 09:59:24 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "minishell.h"

// pour stocker les var d'env dans une liste chainee
t_env	*create_env_list(char **envp)
{
	t_env	*env_list;
	t_env	*new_node;
	char	*equals;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = malloc(sizeof(t_env));
		new_node->raw = ft_strdup(envp[i]);
		*equals = strchr(new_node->raw, '=');
		if (equals)
		{
			*equals = '\0';
			new_node->id = new_node->raw;
			new_node->value = equals + 1;
		}
		new_node->next = env_list;
		env_list = new_node;
		i++;
	}
	return (env_list);
}

void	env_del_one(t_env *env)
{
	if (env->id)
		free(env->id);
	if (env->value)
		free(env->value);
	if (env->raw)
		free(env->raw);
	free(env);
}

//clean la liste chainee des var d'env
void	env_free(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		env_del_one(tmp);
	}
}
