/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_sort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:12:08 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/03 11:13:40 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Trouve la variable avec l'ID minimal parmi les non-imprimées
** @param env: liste des variables d'environnement
** @param min_id: ID minimal actuel (peut être NULL)
** @return: pointeur vers la variable avec l'ID minimal
*/
t_env	*find_min_var(t_env *env, char *min_id)
{
	t_env	*min;

	min = NULL;
	while (env != NULL)
	{
		if (min_id == NULL || ft_strcmp(env->id, min_id) < 0)
		{
			min = env;
			min_id = env->id;
		}
		env = env->next;
	}
	return (min);
}

/*
** Recherche une variable existante dans l'environnement
** @param env: liste des variables d'environnement
** @param name: nom de la variable à rechercher
** @return: pointeur vers la variable si trouvée, NULL sinon
*/
t_env	*find_existing_var(t_env *env, const char *name)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->id, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}
