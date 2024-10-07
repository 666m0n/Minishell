/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:30:55 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/03 14:15:33 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free_stash(stash);
		stash = NULL;
		return (NULL);
	}
	line = NULL;
	read_and_stash(fd, &stash);
	if (stash == NULL)
		return (NULL);
	extract_line(stash, &line);
	clean_stash(&stash);
	if (line && line[0] == '\0')
	{
		free(line);
		free_stash(stash);
		stash = NULL;
		return (NULL);
	}
	return (line);
}

void	read_and_stash(int fd, t_list **stash)
{
	char	*buf;
	int		lus;

	lus = 1;
	while (!found_newline(*stash) && lus != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return ;
		lus = (int)read(fd, buf, BUFFER_SIZE);
		if ((*stash == NULL && lus == 0) || lus == -1)
		{
			free(buf);
			buf = NULL;
			return ;
		}
		buf[lus] = '\0';
		add_to_stash(stash, buf, lus);
		if (*stash == NULL)
			return (free(buf));
		free (buf);
		buf = NULL;
	}
}

void	add_to_stash(t_list **stash, char *buf, int lus)
{
	int		i;
	t_list	*new;
	t_list	*last;

	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	new->next = NULL;
	new->content = malloc(sizeof(char) * (lus + 1));
	if (!new->content)
		return (free(new));
	i = 0;
	while (buf[i] && i < lus)
	{
		new->content[i] = buf[i];
		i++;
	}
	new->content[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new;
		return ;
	}
	last = ft_lst_get_last(*stash);
	last->next = new;
}

void	extract_line(t_list *stash, char **line)
{
	int	i;
	int	y;

	if (stash == NULL)
		return ;
	malloc_line(line, stash);
	if (!*line)
		return ;
	y = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[y++] = stash->content[i];
				break ;
			}
			(*line)[y++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*line)[y] = '\0';
}

void	clean_stash(t_list **stash)
{
	t_list	*last;
	int		i;
	t_list	*new_node;

	if (!stash || !*stash)
		return ;
	last = ft_lst_get_last(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	if (last->content[i] == '\0')
	{
		free_stash(*stash);
		*stash = NULL;
		return ;
	}
	new_node = create_clean_node(last, i);
	if (new_node)
	{
		free_stash(*stash);
		*stash = new_node;
	}
}
