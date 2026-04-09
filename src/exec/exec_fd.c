/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 05:55:29 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/09 05:55:51 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_fds(t_fdsave *save)
{
	dup2(save->stdin_fd, STDIN_FILENO);
	dup2(save->stdout_fd, STDOUT_FILENO);
	close(save->stdin_fd);
	close(save->stdout_fd);
}
