/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 01:59:00 by amartel           #+#    #+#             */
/*   Updated: 2026/02/17 04:57:14 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file utils.h
 */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

typedef struct s_ctx	t_ctx;

/**
 * @brief get content of environement variable
 * @param env struct env
 * @param var the target name of environement variable
 * @return if var exist it return the content of the varible otherwise NULL
 */
char	*ft_getenv(t_env *env, char *var);
/**
 * @brief free context variable of minishell
 * @param ctx context
 */
void	free_ctx(t_ctx *ctx);

#endif
