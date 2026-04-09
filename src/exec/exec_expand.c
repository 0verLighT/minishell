/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 20:01:49 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/09 19:12:24 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Extract variable name starting after the $
 * @param str
 * @param i
 */
static char	*extract_varname(const char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		++(*i);
	return (ft_substr(str, start, *i - start));
}

/**
 * @brief Handle a $ expansion at pos i in str
 * @param str
 * @param i
 * @param ctx
 */
static char	*expand_var(const char *str, int *i, t_ctx *ctx)
{
	char	*ret;
	char	*varname;
	char	*value;

	++(*i);
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

static char	*expand_step(const char *str, int *i, char *result, t_ctx *ctx)
{
	char	*tmp;
	char	buf[2];

	buf[1] = '\0';
	if (str[*i] == '$')
	{
		tmp = expand_var(str, i, ctx);
		if (!tmp)
		{
			free(result);
			return (NULL);
		}
		result = ft_strjoin(result, tmp);
		free(tmp);
	}
	else
	{
		buf[0] = str[*i];
		result = ft_strjoin(result, buf);
		++(*i);
	}
	return (result);
}

char	*ft_expand(const char *str, t_ctx *ctx)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i] && result)
		result = expand_step(str, &i, result, ctx);
	return (result);
}
