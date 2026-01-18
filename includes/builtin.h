/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 22:57:04 by amartel           #+#    #+#             */
/*   Updated: 2026/01/18 06:12:22 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file builtin.h
 */

#ifndef BUILTIN_H
# define BUILTIN_H

#include "minishell.h"

#ifndef SUCCESS
# define SUCCESS 0
#endif

int	env(t_env *env);

#endif