/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   applies_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 02:45:47 by amartel           #+#    #+#             */
/*   Updated: 2026/04/14 02:47:02 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	applies_expand_redirect(t_redirect *redirect, t_ctx *ctx)
{
	char	*expand;

	while (redirect)
	{
		expand = ft_expand(redirect->file, ctx);
		free(redirect->file);
		redirect->file = expand;
		redirect = redirect->next;
	}
}

t_ast_node	*applies_expand(t_ast_node *ast, t_ctx *ctx)
{
	char	*expand;
	size_t	i;

	i = 0;
	if (ast->type == NODE_PIPE)
	{
		applies_expand(ast->data.pair.left, ctx);
		applies_expand(ast->data.pair.right, ctx);
	}
	else if (ast->type == NODE_CMD)
	{
		if (ast->data.cmd.input)
		{
			while (ast->data.cmd.input[i])
			{
				expand = ft_expand(ast->data.cmd.input[i], ctx);
				free(ast->data.cmd.input[i]);
				ast->data.cmd.input[i] = ft_strip_quotes(expand);
				++i;
			}
		}
		applies_expand_redirect(ast->data.cmd.redirects, ctx);
	}
	return (ast);
}

char	*expand_code(char *str, int *i, t_ctx *ctx)
{
	char	*ret;

	if (str[*i] == '?')
	{
		++(*i);
		ret = ft_itoa(ctx->return_code);
		return (ret);
	}
	return (NULL);
}
