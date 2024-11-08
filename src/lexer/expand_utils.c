/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:35:30 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/08 15:18:41 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}

// Retourne la longueur du nom de la variable
size_t	get_var_name_len(const char *str)
{
	size_t	len;

	if (!str || !*str)
		return (0);
	if (*str == '?')
		return (1);
	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	return (len);
}

// Copie la valeur d'une variable dans le résultat
size_t	copy_var_value(char *result, size_t j, char *value, size_t size)
{
	size_t	value_len;

	if (!value)
		return (j);
	value_len = ft_strlen(value);
	if (j + value_len > size)
		value_len = size - j;
	ft_strlcpy(result + j, value, value_len + 1);
	return (j + value_len);
}

// Récupère la valeur d'une variable ou le code de sortie
char	*get_var_value(const char *name, t_lexer *lexer)
{
	t_env	*env;

	if (!name || !*name)
		return (ft_strdup(""));
	if (name[0] == '?')
		return (ft_itoa(lexer->last_exit));
	env = lexer->env;
	while (env)
	{
		if (ft_strcmp(env->id, name) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}
