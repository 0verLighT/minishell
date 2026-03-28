/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 18:14:44 by amartel           #+#    #+#             */
/*   Updated: 2026/03/28 17:30:07 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// this define is needed by vscode ide
#ifndef _POSIX_C_SOURCE
# define _POSIX_C_SOURCE 199309L
#endif
#include "signals.h"

volatile sig_atomic_t	g_sig_code = 0;

void	check_sig(t_ctx *ctx)
{
	if (g_sig_code != 0)
		ctx->return_code = 130;
	g_sig_code = 0;
}

static void	handle_sig(int sig, siginfo_t *info, void *c)
{
	(void)c;
	(void)info;
	if (sig == SIGINT)
	{
		(void)write(1, "\n", 1);
		rl_on_new_line();
		g_sig_code = 130;
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_sig(void)
{
	struct sigaction	sa;
	struct sigaction	act;

	sa.sa_sigaction = handle_sig;
	sa.sa_flags = SA_SIGINFO;
	act.sa_flags = 0;
	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
