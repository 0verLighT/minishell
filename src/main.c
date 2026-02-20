/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 02:32:55 by amartel           #+#    #+#             */
/*   Updated: 2026/02/20 23:18:57 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "input.h"
#include "signals.h"

static void	content_loop(t_ctx *ctx)
{
	char	*line;
	char	*prompt;

	while (1)
	{
		prompt = prompt_fish(ctx);
		line = readline(prompt);
		check_sig(ctx);
		if (!line)
			break ;
		free(prompt);
		if (ft_strcmp(line, "env") == 0)
			ctx->return_code = env(ctx->env);
		if (ft_strcmp(line, "$?") == 0)
		{
			ft_dprintf(0, "%d\n", ctx->return_code);
			ctx->return_code = 0;
		}
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
