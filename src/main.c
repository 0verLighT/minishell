/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 02:32:55 by amartel           #+#    #+#             */
/*   Updated: 2026/04/15 15:58:29 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"
#include "tokenizer.h"

/**
 * @brief generate shell prompt
 * @details fish 🐟
 * @param env struct env
 * @param path jsut string
 * @return the format prompt for readline
 */
static char	*prompt_fish(t_ctx *ctx, char *path)
{
	char	*tmp;

	if (ft_getenv(ctx->env, "USER"))
	{
		tmp = ctx->prompt;
		ctx->prompt = ft_strjoin(tmp, ft_getenv(ctx->env, "USER"));
		free(tmp);
		tmp = ctx->prompt;
		ctx->prompt = ft_strjoin(tmp, ":");
		free(tmp);
	}
	if (ft_strcmp(ft_getenv(ctx->env, "HOME"), ft_getenv(ctx->env, "PWD")) == 0)
		path = "~";
	else
		path = ft_getenv(ctx->env, "PWD");
	if (path)
	{
		tmp = ctx->prompt;
		ctx->prompt = ft_strjoin(tmp, path);
		free(tmp);
	}
	tmp = ctx->prompt;
	ctx->prompt = ft_strjoin(tmp, "$ ");
	free(tmp);
	return (ctx->prompt);
}

static void	procces(char *line, t_ctx *ctx)
{
	t_token		*tokens;
	t_parser	parser;
	t_ast_node	*ast;
	size_t		token_count;

	token_count = 0;
	tokens = tokenizing(line, &token_count);
	if (!tokens)
		return ;
	init_parser(&parser, tokens, (int)token_count);
	ast = parse_pipeline(&parser);
	if (ast)
	{
		ast = applies_expand(ast, ctx);
		exec_node(ast, ctx);
	}
	else
		ctx->return_code = 2;
	free_ast_node(ast);
	free_tokens(tokens, token_count);
}

static void	content_loop(t_ctx *ctx)
{
	char	*line;
	char	*prompt;

	while (1)
	{
		ctx->prompt = ft_strdup("");
		prompt = prompt_fish(ctx, "");
		line = readline(prompt);
		check_sig(ctx);
		if (!line)
			break ;
		if (*line)
		{
			procces(line, ctx);
			if (*line != '\0')
				add_history(line);
		}
		free(prompt);
		free(line);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_ctx	*ctx;
	int		last_return_code;

	(void)ac;
	(void)av;
	init_sig();
	ctx = ft_calloc(1, sizeof(t_ctx));
	init_ctx(ctx, envp);
	content_loop(ctx);
	last_return_code = ctx->return_code;
	free_ctx(ctx);
	ft_dprintf(1, "exit\n");
	return (last_return_code);
}
