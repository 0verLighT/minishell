/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 05:54:40 by amartel           #+#    #+#             */
/*   Updated: 2026/04/15 16:57:42 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_env(t_env *env)
{
	while (env)
	{
		if (ft_strchr(env->var, '='))
			ft_dprintf(1, "%s\n", env->var);
		env = env->next;
	}
	return (SUCCESS);
}
