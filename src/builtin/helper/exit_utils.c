/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 18:18:24 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/14 19:22:23 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/**
 * @brief Skip inital whitespace and check for sign, atoi-like
 * @param str
 * @param tab
 */
static void	handle_whitespaces_sign(char *str, int *tab)
{
	int	idx;

	idx = 0;
	tab[3] = 1;
	while ((str[idx] >= 9 && str[idx] <= 13) || str[idx] == 32)
		idx++;
	if (str[idx] == '+' || str[idx] == '-')
	{
		if (str[idx] == '-')
			tab[3] = -1;
		++idx;
	}
	tab[0] = idx;
}

/**
 * @brief increment result with str, atio-like
 * @param str
 * @param tab
 * @param result
 */
static void	parse_digit(char *str, int *tab, unsigned long long *result)
{
	int					idx;
	unsigned long long	res;

	idx = tab[0];
	res = 0;
	while (str[idx] >= '0' && str[idx] <= '9')
		res = res * 10 + (str[idx++] - 48);
	while ((str[idx] >= 9 && str[idx] <= 13) || str[idx] == 32)
		idx++;
	tab[0] = idx;
	*result = res;
}

/**
 * @brief handle error : non numeric, > LONG_MAX length, overflow
 * @param str
 * @param tab
 * @param result
 */
static void	error_handling(char *str, int *tab, unsigned long long *result)
{
	if (str[tab[0]]
		|| tab[0] - tab[1] > 20
		|| (tab[3] == -1 && (*result - 1) > LONG_MAX)
		|| (tab[3] == 1 && *result > LONG_MAX))
		tab[2] = 1;
}

int	parse_exitcode(char *str, int *err_flag)
{
	int					tab[4];
	unsigned long long	result;
	int					exitcode;

	tab[0] = 0;
	tab[1] = 0;
	tab[2] = 0;
	tab[3] = 1;
	handle_whitespaces_sign(str, tab);
	tab[1] = tab[0];
	parse_digit(str, tab, &result);
	error_handling(str, tab, &result);
	*err_flag = tab[2];
	exitcode = (int)((result * tab[3]) % 256);
	return (exitcode);
}
