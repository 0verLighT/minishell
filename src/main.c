/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 02:32:55 by amartel           #+#    #+#             */
/*   Updated: 2026/01/19 01:49:20 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *prompt_fish(char **envp)
{
	char	*line;
	char	*tmp;
	
	// usrename@hostanme:PWD$
	line = ft_strdup("");
	line = ft_strjoin(line, getenv("USER"));
	line = ft_strjoin(line, ":");
	// line = ft_strjoin(line, getenv("HOSTNAME"));
	if (ft_strcmp(getenv("HOME"), getenv("PWD")) == 0)
		tmp = ft_strdup("~");
	else
		tmp = ft_strdup(getenv("PWD"));
	line = ft_strjoin(line, tmp);
	line = ft_strjoin(line, "$ ");
	return (line);
}

int main(int ac, char **av, char **envp)
{
	char	*line;
	t_ctx	*ctx;

	ctx = ft_calloc(1, sizeof(t_ctx));
	line = readline(prompt_fish(envp));
	init_ctx(ctx, envp);
	while (line != NULL)
	{
		add_history(line);
		if (strcmp(line, "env") == 0)
			env(ctx->env);
		free(line);
		line = readline(prompt_fish(envp));
	}
	return (0);
}
