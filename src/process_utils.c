/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:00:00 by emmanuel          #+#    #+#             */
/*   Updated: 2024/11/04 10:41:59 by emmanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

pid_t   create_child_process(void)
{
    return (fork());
}

void    exec_in_child(t_command *cmd, t_ctx *ctx)
{
    (void)cmd;
    (void)ctx;
    exit(1); // Temporaire, à implémenter complètement
}

int     wait_child(pid_t pid)
{
    int status;

    if (waitpid(pid, &status, 0) == -1)
        return (ERROR);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (ERROR);
}
