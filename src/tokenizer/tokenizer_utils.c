/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 21:21:31 by jdessoli          #+#    #+#             */
/*   Updated: 2026/01/26 02:32:59 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	strskip(char *str, char *charset)
{
	int i;
	int j;
	int found;
	
	i = 0;
	while (str[i])
	{
		j = 0;
		found = 0;
		while (charset[j])
		{
			if (charset[j] == str[i])
			{
				found = 1;
				break;
			}
			j++;
		}
		if (!found)
			break;
		i++;
	}
	return (i);
}

int	strfind(char *str, char *charset)
{
	int	i;
	int	j;
	
	i = 0;
	while (str[i])
	{
		j = 0;
		while (charset[j])
		{
			if (charset[j] == str[i])
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

int	count_token(char *str)
{
	int	i;
	int	token_nb;
	
	i = 0;
	token_nb = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (is_space(str[i]) && str[i])
			i++;
		if (str[i] != 0)
		{
			token_nb++;
			while (!is_space(str[i]) && str[i])
				i++;
		}
	}
	return (token_nb);
}

t_slice *token_maker(char *str)
{
	t_slice	*token;
	int 	token_start;
	int		len;
	
	if (!str)
		return (NULL);
	token = malloc(sizeof(t_slice));
	if (!token)
		return (NULL);
	token_start = strskip(str, " \t\n");
	len = token_start;
	while (!is_space(str[len]) && str[len])
		len++;
	token->len = len - token_start;
	token->ptr = malloc(token->len + 1);
	if (!token->ptr)
	{
		free(token);
		return (NULL);
	}
	ft_memcpy(token->ptr, str + token_start, token->len);
	token->ptr[token->len] = '\0';
	return (token);
}
