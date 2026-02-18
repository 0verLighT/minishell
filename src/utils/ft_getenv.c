/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 01:58:10 by amartel           #+#    #+#             */
/*   Updated: 2026/02/17 04:57:55 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_getenv(t_env *env, char *var)
{
	const size_t	len = ft_strlen(var);

	while (env)
	{
		if (ft_strncmp(env->var, var, len) == 0)
			return (env->var + len + 1);
		env = env->next;
	}
	return (NULL);
}
