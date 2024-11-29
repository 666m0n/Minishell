/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 10:28:54 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/29 17:40:43 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Traite un argument de la commande export
** - Vérifie la validité de l'identifiant
** - Met à jour ou crée la variable si valide 
** @param arg: argument à traiter (format: VAR ou VAR=value)
** @param ctx: contexte du shell
** @return: SUCCESS si ok, ERROR si échec
*/
static int handle_export_arg(const char *arg, t_ctx *ctx)
{  
    if (!arg)
        return (handle_builtin_error("export", "", "not a valid identifier"));
    if (!*arg || arg[0] == '=')
        return (handle_builtin_error("export", "", "not a valid identifier"));
    if (!is_valid_identifier(arg))
        return (handle_builtin_error("export", arg, "not a valid identifier"));
    if (!update_env_variable(ctx, arg))
        return (ERROR);
    return (SUCCESS);
}

/*
** Trouve la prochaine variable dans l'ordre alphabétique
** @param env: liste des variables
** @param last: dernière variable traitée (NULL pour première)
** @return: pointeur vers la prochaine variable ou NULL
*/
static t_env *find_next_var(t_env *env, char *last)
{
    t_env *next;
    t_env *current;

    next = NULL;
    current = env;
    while (current)
    {
        if ((!last || ft_strcmp(current->id, last) > 0)
            && (!next || ft_strcmp(current->id, next->id) < 0))
            next = current;
        current = current->next;
    }
    return (next);
}

/*
** Affiche une variable au format export
** Format: export name="value" ou export name
** @param var: variable à afficher
*/
static void print_export_var(t_env *var)
{
    if (!var || !var->id)
        return ;
    ft_putstr_fd("export ", STDOUT_FILENO);
    ft_putstr_fd(var->id, STDOUT_FILENO);
    if (var->value)
    {
        ft_putstr_fd("=\"", STDOUT_FILENO);
        ft_putstr_fd(var->value, STDOUT_FILENO);
        ft_putchar_fd('\"', STDOUT_FILENO);
    }
    ft_putchar_fd('\n', STDOUT_FILENO);
}

/*
** Affiche les variables d'environnement triées par ordre alphabétique
** @param ctx: contexte du shell
** @return: SUCCESS toujours
*/
static int display_sorted_env(t_ctx *ctx)
{
    t_env   *current;
    char    *last;
    int     i;
    int     count;

    count = 0;
    current = ctx->envp;
    while (current && ++count)
        current = current->next;

    last = NULL;
    i = 0;
    while (i < count)
    {
        current = find_next_var(ctx->envp, last);
        if (current)
            print_export_var(current);
        last = current->id;
        i++;
    }
    return (SUCCESS);
}

/*
** Implémente la commande export sans options
** - Sans argument : affiche les variables triées
** - Avec arguments : valide et traite chaque argument
** @param cmd: structure contenant la commande et ses arguments 
** @param ctx: contexte du shell
** @return: SUCCESS si ok, ERROR sinon
*/
int    builtin_export(t_cmd *cmd, t_ctx *ctx)
{
   int    i;
   int    status;
   
   i = 0;
   while (cmd->args && cmd->args[i])
       i++;
   if (!cmd || !cmd->args)
       return (ERROR);
   if (!cmd->args[1])  // ICI si "" était traité comme une chaine vide cette condition ne serait pas déclenchée.
       return (display_sorted_env(ctx));
   status = SUCCESS;
   i = 1;
   while (cmd->args[i])
   {
       if (handle_export_arg(cmd->args[i], ctx) != SUCCESS)
           status = ERROR;
       i++;
   }
   return (status);
}
