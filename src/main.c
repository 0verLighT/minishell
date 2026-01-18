/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 02:32:55 by amartel           #+#    #+#             */
/*   Updated: 2026/01/18 06:11:26 by amartel          ###   ########.fr       */
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
	line = ft_strjoin(line, "@");
	// line = ft_strjoin(line, getenv("HOSTNAME"));
	if (ft_strcmp(getenv("HOME"), getenv("PWD")) == 0)
		tmp = ft_strdup("~");
	else
		tmp = ft_strdup(getenv("PWD"));
	tmp = ft_strjoin(line, tmp);
	tmp = ft_strjoin(line, "$ ");
	free(line);
	return (tmp);
}

int main(int ac, char **av, char **envp)
{
	char	*line;
	t_ctx	ctx;

	
	line = readline("Hello");
	
	while (line != NULL)
	{
		add_history(line);
		if (strcmp(line, "env") == 0)
			env()
		free(line);
		line = readline("Hello");
	}
	return (0);
}
