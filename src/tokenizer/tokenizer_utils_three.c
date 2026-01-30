/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_three.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 02:39:41 by jdessoli          #+#    #+#             */
/*   Updated: 2026/01/26 02:40:42 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	free_tokens(t_token *tokens)
{
	int	i;
	
	if (!tokens)
		return;
	i = 0;
	while (tokens[i].index != -1)
	{
		free(tokens[i].content.ptr);
		i++;
	}
	free(tokens);
}
