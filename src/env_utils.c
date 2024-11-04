/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:56:15 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/04 10:56:51 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env   *create_env_list(char **envp)
{
    t_env   *env_list;
    t_env   *new_node;
    char    *equals;
    int     i;

    env_list = NULL;
    i = 0;
    while (envp && envp[i])
    {
        new_node = malloc(sizeof(t_env));
        if (!new_node)
            return (NULL);
        new_node->raw = ft_strdup(envp[i]);
        if (!new_node->raw)
        {
            free(new_node);
            return (NULL);
        }
        equals = ft_strchr(new_node->raw, '=');
        if (equals)
        {
            *equals = '\0';
            new_node->id = new_node->raw;
            new_node->value = equals + 1;
        }
        else
        {
            new_node->id = new_node->raw;
            new_node->value = NULL;
        }
        new_node->next = env_list;
        env_list = new_node;
        i++;
    }
    return (env_list);
}

void    env_del_one(t_env *env)
{
    if (!env)
        return ;
    if (env->raw)
        free(env->raw);
    free(env);
}

void    free_all(t_ctx *ctx)
{
    t_env   *current;
    t_env   *next;

    if (!ctx)
        return ;
    current = ctx->envp;
    while (current)
    {
        next = current->next;
        env_del_one(current);
        current = next;
    }
    if (ctx->lexer_output)
        free_token(ctx->lexer_output);  // Assurez-vous d'avoir cette fonction
    free(ctx);
}
