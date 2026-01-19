/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 02:32:55 by amartel           #+#    #+#             */
/*   Updated: 2026/01/19 01:12:57 by amartel          ###   ########.fr       */
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
	char *line;
	
	while ((line = readline(prompt_fish(envp))) != NULL)
	{	
		add_history(line);
		printf("%s\n", line);
	}
	return (0);
}
