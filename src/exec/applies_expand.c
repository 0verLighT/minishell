/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   applies_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 02:45:47 by amartel           #+#    #+#             */
/*   Updated: 2026/04/14 18:27:12 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	applies_expand_redirect(t_redirect *redirect, t_ctx *ctx)
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
	char	**new_input;

	if (ast->type == NODE_PIPE)
	{
		applies_expand(ast->data.pair.left, ctx);
		applies_expand(ast->data.pair.right, ctx);
		return (ast);
	}
	if (ast->type != NODE_CMD || !ast->data.cmd.input)
		return (ast);
	new_input = build_new_input(ast->data.cmd.input, ctx);
	free(ast->data.cmd.input);
	ast->data.cmd.input = new_input;
	applies_expand_redirect(ast->data.cmd.redirects, ctx);
	return (ast);
}
