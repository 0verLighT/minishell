/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isoperator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 01:05:00 by amartel           #+#    #+#             */
/*   Updated: 2026/03/30 23:22:28 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	isoperator(char c)
{
	if (c == '<' || c == '|' || c == '>')
		return (1);
	return (0);
}

int	isdoubleop(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (isoperator(str[i]))
	{
		if (str[i + 1] == '<' || str[i + 1] == '>')
			return (1);
		else
			return (0);
	}
	else
		return (0);
}
