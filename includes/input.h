/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 01:53:08 by amartel           #+#    #+#             */
/*   Updated: 2026/02/17 04:57:29 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file input.h
 */

#ifndef INPUT_H
# define INPUT_H

# include "minishell.h"
# include "utils.h"

/**
 * @brief generate shell prompt
 * @details fish 🐟
 * @param env struct env
 * @return the format prompt for readline
 */
char	*prompt_fish(t_ctx *ctx);
#endif
