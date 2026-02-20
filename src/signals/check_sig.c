/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sig.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 22:49:57 by amartel           #+#    #+#             */
/*   Updated: 2026/02/20 23:26:06 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include "minishell.h"

void	check_sig(t_ctx *ctx)
{
	if (g_sig_code != 0)
		ctx->return_code = 130;
	g_sig_code = 0;
}
