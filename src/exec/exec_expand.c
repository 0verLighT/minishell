/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 20:01:49 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/14 03:33:06 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Extract variable name starting after the $
 * @param str
 * @param i
 */
static char	*extract_varname(char *str, int *i)
{
	int		start;
	char	*string;

	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		++(*i);
	string = ft_substr(str, start, *i - start);
	return (string);
}

/**
 * @brief Handle a $ expansion at pos i in str
 * @param str
 * @param i
 * @param ctx
 */
static char	*expand_var(char *str, int *i, t_ctx *ctx)
{
	char	*ret;
	char	*varname;
	char	*value;

	++(*i);
	ret = expand_code(str, i, ctx);
	if (ret)
		return (ret);
	if (!str[*i] || (!ft_isalpha(str[*i]) && str[*i] != '_'))
	{
		ret = ft_strdup("$");
		return (ret);
	}
	varname = extract_varname(str, i);
	if (!varname)
		return (NULL);
	value = ft_getenv(ctx->env, varname);
	free(varname);
	if (!value)
	{
		ret = ft_strdup("");
		return (ret);
	}
	ret = ft_strdup(value);
	return (ret);
}

static char	*expand_step(char *str, int *i, t_ctx *ctx, char *q)
{
	char	buf[2];
	char	*buffer;

	if ((str[*i] == '\'' || str[*i] == '"') && !*q)
		*q = str[*i];
	else if (*q && str[*i] == *q)
		*q = 0;
	if (str[*i] == '$' && *q != '\'')
		return (expand_var(str, i, ctx));
	buf[0] = str[*i];
	buf[1] = '\0';
	++(*i);
	buffer = ft_strdup(buf);
	return (buffer);
}

char	*ft_expand(char *str, t_ctx *ctx)
{
	char	*result;
	int		i;
	char	*tmp;
	char	q;
	char	*old_result;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	q = 0;
	while (str[i] && result)
	{
		tmp = expand_step(str, &i, ctx, &q);
		if (!tmp)
		{
			free(tmp);
			return (NULL);
		}
		old_result = result;
		result = ft_strjoin(old_result, tmp);
		free(tmp);
	}
	return (result);
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
