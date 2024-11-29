/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:05:03 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/29 17:41:08 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Trouve une variable dans l'environnement par son nom
** @param env: liste des variables d'environnement
** @param name: nom de la variable à chercher (peut inclure '=value')
** @return: pointeur vers la variable si trouvée, NULL sinon
** Note: compare jusqu'au '=' s'il existe dans name
*/
t_env    *find_existing_var(t_env *env, const char *name)
{
    t_env    *current;
    int     len;

    if (!name || (name[0] == '_' && name[1] == '\0'))
        return (NULL);
    
    // Calcule la longueur jusqu'au '=' ou fin
    len = 0;
    while (name[len] && name[len] != '=')
        len++;

    current = env;
    while (current)
    {
        if (!ft_strncmp(current->id, name, len) && !current->id[len])
            return (current);
        current = current->next;
    }
    return (NULL);
}

/*
** Crée une nouvelle variable d'environnement
** @param arg: chaîne complète (nom=valeur ou nom)
** @param value: valeur déjà extraite (peut être NULL)
** @return: nouvelle variable allouée, NULL si erreur
*/
t_env    *create_var(const char *arg, char *value)
{
    t_env   *new;
    int     len;

    len = 0;
    while (arg[len] && arg[len] != '=')
        len++;
    new = malloc(sizeof(t_env));
    if (!new)
        return (NULL);

    new->id = ft_strndup(arg, len);
    new->value = value;
    new->raw = ft_strdup(arg);
    new->next = NULL;
    if (!new->id || !new->raw)
    {
        free_env_var(new);
        return (NULL);
    }
    return (new);
}

/*
** Extrait la valeur après le signe égal
** @param arg: chaîne au format "nom=valeur"
** @return: valeur allouée ou NULL si pas de '='
** Note: retourne une chaîne vide si rien après le '='
*/
char    *extract_value(const char *arg)
{
    char    *eq;

    eq = ft_strchr(arg, '=');
    if (!eq)
        return (NULL);
    return (ft_strdup(eq + 1));
}

/*
** Met à jour ou crée une variable d'environnement
** - Si la variable existe déjà, met à jour sa valeur
** - Sinon, crée une nouvelle variable
** @param ctx: contexte du shell
** @param arg: argument complet (VAR=value ou VAR)
** @return: pointeur sur la variable mise à jour/créée, NULL si erreur
*/
t_env    *update_env_variable(t_ctx *ctx, const char *arg)
{
    t_env    *var;
    char    *value;
    
    value = extract_value(arg);
    var = find_existing_var(ctx->envp, arg);
    if (var)
    {
        if (var->value)
            free(var->value);
        free(var->raw);
        var->value = value;
        var->raw = ft_strdup(arg);
        if (!var->raw)
            return (NULL);
    }
    else
    {
        var = create_var(arg, value);
        if (!var)
            return (NULL);
        var->next = ctx->envp;
        ctx->envp = var;
    }
    return (var);
}

/*
** Vérifie si une chaîne est un identifiant valide pour une variable
** - Doit commencer par une lettre ou underscore
** - Ne peut contenir que lettres, chiffres, underscores
** - S'arrête au premier '=' si présent
** @param str: chaîne à vérifier
** @return: TRUE si valide, FALSE sinon
*/
int    is_valid_identifier(const char *str)
{
    if (!str || !*str)
        return (FALSE);
    if (!ft_isalpha(*str) && *str != '_')
        return (FALSE);
    str++;
    while (*str && *str != '=')
    {
        if (!ft_isalnum(*str) && *str != '_')
            return (FALSE);
        str++;
    }

    return (TRUE);
}

/*
** Libère tous les composants d'une variable d'environnement
** @param var: variable d'environnement à libérer
** Note: libère raw, id, value et la structure elle-même
** Note: gère le cas où var est NULL ou certains composants sont NULL
*/
void	free_env_var(t_env *var)
{
	if (!var)
		return ;
	if (var->raw)
		free(var->raw);
	if (var->id)
		free(var->id);
	if (var->value)
		free(var->value);
	free(var);
}
