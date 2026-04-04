/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 10:24:40 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/04 20:30:55 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/**
 * @brief 
 */
static char	*get_current_dir_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		builtin_error("pwd", NULL, strerror(errno));
	return (cwd);
}

int	ft_pwd(void)
{
	char	*cwd;

	cwd = get_current_dir_pwd();
	if (!cwd)
		return (1);
	ft_dprintf(1, "%s\n", cwd);
	free(cwd);
	return (SUCCESS);
}
