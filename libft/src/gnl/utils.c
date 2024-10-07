/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:59:48 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/03 14:13:29 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

t_list	*create_clean_node(t_list *last, int i)
{
	t_list	*clean;
	int		y;

	clean = malloc(sizeof(t_list));
	if (clean == NULL)
		return (NULL);
	clean->next = NULL;
	clean->content = malloc(sizeof(char) * \
		((ft_strlen(last->content) - i + 1)));
	if (!clean->content)
	{
		free(clean);
		return (NULL);
	}
	y = 0;
	while (last->content[i])
		clean->content[y++] = last->content[i++];
	clean->content[y] = '\0';
	return (clean);
}
