/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 05:55:29 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/09 17:09:29 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	restore_fds(t_fdsave *save)
{
	dup2(save->stdin_fd, STDIN_FILENO);
	dup2(save->stdout_fd, STDOUT_FILENO);
	close(save->stdin_fd);
	close(save->stdout_fd);
}
