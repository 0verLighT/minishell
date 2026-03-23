/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 18:18:24 by jdessoli          #+#    #+#             */
/*   Updated: 2026/03/23 16:22:26 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
 
//skip inital whitespace and check for sign, atoi-like
static void	handle_whitespaces_sign(char *str, int *tab)
{
	int	idx;

	idx = 0;
	tab[3] = 1;
	while ((str[idx] => 9 && str[idx] <= 13) || str[idx] == 32)
		idx++;
	if (str[idx] == '+' || str[idx] == '-')
		if (str[idx] == '-')
			tab[3] = -1;
	tab[0] = idx;
}

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

//The 4 hypothesis of the if : non numeric leftover, > LONG_MAX length
//negative overflow, positive overflow
static void	error_handling(char *str, int *tab, unsigned long long *result)
{

	if (str[tab[0]]
    || tab[0] - tab[1] > 20
    || (tab[3] == -1 && (*result - 1) > LONG_MAX)
    || (tab[3] == 1  && *result > LONG_MAX))
    tab[2] = 1;
}

//in tab, 0 is for i, 1 for j, 2 for err_flag, 3 for sign
//the modulo is to imitate shell exit code
int	parse_exitcode(char *str, int *err_flag)
{
	int			*tab[4];
	int			exitcode;
	unsigned long long	*result;

	tab = malloc(sizeof(int) * 4);
	if (!tab)
		return 0;
	result = malloc(sizeof(unsigned long long));
	if (!result)
	{
		free(tab);
		return 0;
	}
	handle_whitespaces_sign(str, tab, sign);
	tab[1] = tab[0];
	parse_digit(str, tab, result);
	error_handling(str, tab, result);
	exitcode = (int)((*result * tab[3]) % 256);
	free(tab);
	fee(result);
	return (exitcode);
}
