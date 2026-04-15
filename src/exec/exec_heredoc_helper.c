/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 05:36:13 by amartel           #+#    #+#             */
/*   Updated: 2026/04/15 05:36:55 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	post_fill_heredoc(int fd_copy, char *line)
{
	dup2(fd_copy, 0);
	close(fd_copy);
	rl_replace_line("", 0);
	if (line)
		free(line);
}
