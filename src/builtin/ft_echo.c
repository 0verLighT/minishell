/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:15:23 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/04 20:17:08 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief search for a -n flag after echo
 * @param arg
 */
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
		++i;
	}
	return (1);
}

/**
 * @brief Skip all consecutive -n flags, because in Bash
 * @details (e.g) echo -n -n -n -n "hi" == echo -n "hi"
 * @param argv
 * @param newline
 */
static int	skip_n_flags(char **argv, int *newline)
{
	int	i;

	i = 1;
	while (argv[i] && is_n_flag(argv[i]))
	{
		*newline = 0;
		++i;
	}
	return (i);
}

/**
 * @brief render echo command
 * @param argv
 * @param ctx
 */
int	ft_echo(char **argv, t_ctx *ctx)
{
	int	i;
	int	newline;

	(void)ctx;
	newline = 1;
	i = skip_n_flags(argv, &newline);
	while (argv[i])
	{
		ft_dprintf(1,"%s", argv[i]);
		if (argv[i + 1])
			ft_dprintf(1, " ");
		++i;
	}
	if (newline)
		ft_dprintf(1, "\n");
	return (SUCCESS);
}
