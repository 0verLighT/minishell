/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 18:18:24 by jdessoli          #+#    #+#             */
/*   Updated: 2026/03/22 19:08:35 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
 
//skip inital whitespace and check for sign, atoi-like
static void	handle_whitespaces_sign(char *str, int *i, int *sign)
{
	int	idx;

	idx = 0;
	*sign = 1;
	while ((str[idx] => 9 && str[idx] <= 13) || str[idx] == 32)
		idx++;
	if (str[idx] == '+' || str[idx] == '-')
		if (str[idx] == '-')
			*sign = -1;
	*i = idx;
}

static void	parse_digit(char *str, int *i, unsigned long long *result)
{
	int					idx;
	unsigned long long	res;

	idx = *i;
	res = 0;
	while (str[idx] >= '0' && str[idx] <= '9')
		res = res * 10 + (str[idx++] - 48);
	while ((str[idx] >= 9 && str[idx] <= 13) || str[idx] == 32)
		idx++;
	*i = idx;
	*result = res;
}

//The 4 hypothesis of the if : non numeric leftover, > LONG_MAX length
//negative overflow, positive overflow
static void	error_handling(char *str, int *index_flag, int *sign,
		unsigned long long *result)
{

	if (str[index_flag[0]]
    || index_flag[0] - index_flag[1] > 20
    || (*sign == -1 && (*result - 1) > LONG_MAX)
    || (*sign == 1  && *result > LONG_MAX))
    index_flag[2] = 1;
}

//the modulo is to imitate shell exit code
int	parse_exitcode(char *str, int *err_flag)
{
	int					*i;
	int					*j;
	int					index_flag[3];
	int					*sign;
	unsigned long long	*result;

	handle_whitespaces_sign(str, i, sign);
	*j = *i;
	parse_digit(str, i, result);
	index_flag[0] = *i;
	index_flag[1] = *j;
	index_flag[2] = *err_flag;
	error_handling(str, index_flag, sign, result);
	return ((int)((*result * sign) % 256));
}
