/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:13:10 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/05 11:13:46 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strndup(const char *s, size_t n)
{
    size_t len = 0;
    char *dup;

    while (len < n && s[len])
        len++;

    dup = malloc(len + 1);
    if (!dup)
        return (NULL);

    for (size_t i = 0; i < len; i++)
        dup[i] = s[i];
    dup[len] = '\0';

    return (dup);
}
