/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 22:59:23 by amartel           #+#    #+#             */
/*   Updated: 2026/04/09 19:35:12 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file signals.h
 */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct s_ctx			t_ctx;

extern volatile sig_atomic_t	g_sig_code;

/**
 * @brief check if SIGINT was press to set return_code to 130
 * @param ctx
 */
void							check_sig(t_ctx *ctx);
/**
 * @brief init signal of minishell
 */
void							init_sig(void);

#endif
