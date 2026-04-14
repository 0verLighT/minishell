/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 20:01:49 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/14 18:28:45 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*expand_and_strip(char *token, t_ctx *ctx, int *had_quotes)
{
	char	*expand;
	char	*stripped;

	*had_quotes = (ft_strchr(token, '\'') || ft_strchr(token, '"'));
	expand = ft_expand(token, ctx);
	free(token);
	if (!expand)
		return (NULL);
	stripped = ft_strip_quotes(expand);
	free(expand);
	return (stripped);
}

char	**build_new_input(char **old_input, t_ctx *ctx)
{
	char	**new_input;
	char	*stripped;
	int		had_quotes;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (old_input[i])
		++i;
	new_input = ft_calloc(i + 1, sizeof(char *));
	if (!new_input)
		return (NULL);
	i = 0;
	while (old_input[i])
	{
		stripped = expand_and_strip(old_input[i], ctx, &had_quotes);
		if (stripped && (stripped[0] != '\0' || had_quotes))
			new_input[j++] = stripped;
		else
			free(stripped);
		++i;
	}
	new_input[j] = NULL;
	return (new_input);
}

char	*ft_strip_quotes(char *str)
{
	char	*new;
	int		i;
	int		j;
	char	q;

	new = ft_calloc(sizeof(char), (ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	q = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && !q)
			q = str[i++];
		else if (q && str[i] == q)
		{
			q = 0;
			++i;
		}
		else
			new[j++] = str[i++];
	}
	return (new);
}
