/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 02:32:55 by amartel           #+#    #+#             */
/*   Updated: 2026/02/17 04:43:31 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "input.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_ctx	*ctx;
	char	*prompt;

	(void)ac;
	(void)av;
	init_sig();
	ctx = ft_calloc(1, sizeof(t_ctx));
	init_ctx(ctx, envp);
	while (1)
	{
		prompt = prompt_fish(ctx);
		line = readline(prompt);
		if (!line)
			break ;
		free(prompt);
		if (ft_strcmp(line, "env") == 0)
			env(ctx->env);
		add_history(line);
		free(line);
	}
	free_ctx(ctx);
	ft_dprintf(1, "exit\n");
	return (0);
}
