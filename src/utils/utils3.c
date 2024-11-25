/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:40:50 by sviallon          #+#    #+#             */
/*   Updated: 2024/11/25 14:49:27 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//liste chainee du contexte du prgrm
t_ctx	*init_ctx(char **envp)
{
	t_ctx	*ctx;

	ctx = malloc(sizeof(t_ctx));
	if (!ctx)
		return (NULL);
	ctx->envp = create_env_list(envp);
	if (!ctx->envp)
	{
		free(ctx);
		return (NULL);
	}
	ctx->def_in = STDIN_FILENO;
	ctx->def_out = STDOUT_FILENO;
	ctx->exit_code = 0;
	return (ctx);
}

int	check_line(char *line)
{
	if (line[0] == '\0')
		return (TRUE);
	return (FALSE);
}

char	*ft_realloc(void *s, int old_size, int new_size)
{
	char	*ret;

	if (!new_size || new_size <= 0)
		return (free(s), NULL);
	ret = malloc(new_size);
	if (!ret)
		return (free(s), NULL);
	if (s)
	{
		ft_memcpy(ret, s, old_size);
		free(s);
	}
	return (ret);
}

// Join avec free du premier argument
char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

//calcule la taille d'une variable
size_t	get_var_len(char *s, size_t *i)
{
	size_t	y;

	y = *i;
	if (s[y + 1] >= '0' && s[y + 1] <= '9')
		return (1);
	else
	{
		y++;
		while (s[y] && ((s[y] >= 'a' && s[y] <= 'z')
				|| (s[y] >= 'A' && s[y] <= 'Z')
				|| (s[y] >= '0' && s[y] <= '9')
				|| s[y] == '_'))
			y++;
		return (y - *i - 1);
	}
}
