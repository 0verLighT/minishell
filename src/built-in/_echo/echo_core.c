/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:15:23 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/03 15:25:56 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//search for a -n flag after echo
static int	is_n_flag(const char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

//Skip all consecutive -n flags, because in Bash
//echo -n -n -n -n "hi" == echo -n "hi"
static int	skip_n_flags(char **argv, int *newline)
{
	int	i;

	i = 1;
	while (argv[i] && is_n_flag(argv[i]))
	{
		*newline = 0;
		i++;
	}
	return (i);
}

//We have to cast ctx as void, so the args of echo core
//still match the dispatch table of builtin.h
//To see more, check the struct under the enum in the .h
int	echo_core(char **argv, t_ctx *ctx)
{
	int	i;
	int	newline;

	(void)ctx;
	newline = 1;
	i = skip_n_flags(argv, &newline);
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (SUCCESS);
}
