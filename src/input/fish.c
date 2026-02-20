/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fish.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 01:52:23 by amartel           #+#    #+#             */
/*   Updated: 2026/02/20 22:54:33 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	*prompt_fish(t_ctx *ctx)
{
	char	*tmp;

	ctx->prompt = ft_strjoin(NULL, ft_getenv(ctx->env, "USER"));
	ctx->prompt = ft_strjoin(ctx->prompt, ":");
	if (ft_strcmp(ft_getenv(ctx->env, "HOME"), ft_getenv(ctx->env, "PWD")) == 0)
		tmp = "~";
	else
		tmp = ft_getenv(ctx->env, "PWD");
	ctx->prompt = ft_strjoin(ctx->prompt, tmp);
	ctx->prompt = ft_strjoin(ctx->prompt, "$ ");
	return (ctx->prompt);
}
