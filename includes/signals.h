/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 22:59:23 by amartel           #+#    #+#             */
/*   Updated: 2026/02/20 23:17:46 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file signals.h
 */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct s_ctx			t_ctx;

extern volatile sig_atomic_t	g_sig_code;

void							check_sig(t_ctx *ctx);
void							init_sig(void);

#endif
