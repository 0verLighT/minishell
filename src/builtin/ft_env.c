/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 05:54:40 by amartel           #+#    #+#             */
/*   Updated: 2026/04/04 19:58:27 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_env(t_env *env)
{
	while (env)
	{
		ft_dprintf(1, "%s\n", env->var);
		env = env->next;
	}
	return (SUCCESS);
}
