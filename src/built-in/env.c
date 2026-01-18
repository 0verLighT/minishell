/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 05:54:40 by amartel           #+#    #+#             */
/*   Updated: 2026/01/18 06:05:44 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	env(t_env *env)
{
	while (env->var)
	{
		printf("%s\n", env->var);
		env = env->next;
	}
	return (SUCCESS);
}