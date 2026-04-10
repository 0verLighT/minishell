/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 02:32:55 by amartel           #+#    #+#             */
/*   Updated: 2026/04/10 20:25:16 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"
#include "tokenizer.h"

/**
 * @brief generate shell prompt
 * @details fish 🐟
 * @param env struct env
 * @return the format prompt for readline
 */
static char	*prompt_fish(t_ctx *ctx)
{
	char	*tmp;

	ctx->prompt = ft_strdup("");
	if (ft_getenv(ctx->env, "USER"))
	{
		ctx->prompt = ft_strjoin(NULL, ft_getenv(ctx->env, "USER"));
		ctx->prompt = ft_strjoin(ctx->prompt, ":");
	}
	if (ft_strcmp(ft_getenv(ctx->env, "HOME"), ft_getenv(ctx->env, "PWD")) == 0)
		tmp = "~";
	else if (ft_getenv(ctx->env, "PWD"))
		tmp = ft_getenv(ctx->env, "PWD");
	else
		tmp = NULL;
	ctx->prompt = ft_strjoin(ctx->prompt, tmp);
	ctx->prompt = ft_strjoin(ctx->prompt, "$ ");
	return (ctx->prompt);
}

static void procces(char *line, t_ctx *ctx)
{
	t_token		*tokens;
	t_parser	*parser;
	t_ast_node	*ast;
	size_t		token_count;

	token_count = 0;
	tokens = tokenizing(line, &token_count);
	if (!tokens)
		return ;
	parser = malloc(sizeof(t_parser));
	if (!parser)
		free(parser);
	ast = malloc(sizeof(t_ast_node));
	if (!ast)
		free(ast);
	init_parser(parser, tokens, (int)token_count);
	ast = parse_pipeline(parser);
	exec_node(ast, ctx);
	free(ast);
	free(tokens);
	free(parser);
}

static void	content_loop(t_ctx *ctx)
{
	char	*line;
	char	*prompt;

	while (1)
	{
		prompt = prompt_fish(ctx);
		line = readline(prompt);
		check_sig(ctx);
		if (!line)
			break ;
		procces(line, ctx);
		free(prompt);
		if (line[0] != '\0')
			add_history(line);
		free(line);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_ctx	*ctx;

	(void)ac;
	(void)av;
	init_sig();
	ctx = ft_calloc(1, sizeof(t_ctx));
	init_ctx(ctx, envp);
	content_loop(ctx);
	free_ctx(ctx);
	ft_dprintf(1, "exit\n");
	return (0);
}
