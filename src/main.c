/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 02:32:55 by amartel           #+#    #+#             */
/*   Updated: 2026/03/22 23:55:59 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"
#include "tokenizer.h"

/**
 * @brief generate shell prompt
 * @details fish 🐟
 * @param env struct env
 * @return the format prompt for readline
 */
static char	*prompt_fish(t_ctx *ctx)
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

static void	content_loop(t_ctx *ctx)
{
	char	*line;
	char	*prompt;
	t_token	*t;

	while (1)
	{
		prompt = prompt_fish(ctx);
		line = readline(prompt);
		check_sig(ctx);
		if (!line)
			break ;
		free(prompt);
		t = tokenizing(line);
		if (t)
		{
		int i = 0;
			while (t[i].content.ptr != NULL)
			{
				printf("Token [%d] : content = {%s}, len = %zu\n",
					i, t[i].content.ptr, t[i].content.len);
			++i;
			}
		}
		free(t->content.ptr);
		free(t);
		if (line[0] != '\0')
			add_history(line);
		free(line);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_ctx	*ctx;

	(void)ac;
	(void)av;
	init_sig();
	ctx = ft_calloc(1, sizeof(t_ctx));
	init_ctx(ctx, envp);
	content_loop(ctx);
	free_ctx(ctx);
	ft_dprintf(1, "exit\n");
	return (0);
}
