/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 02:33:3 by jdessoli          #+#    #+#             */
/*   Updated: 2026/02/26 01:47:34 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"

static size_t	get_token_len_helper(char *str, size_t pos,
	size_t len, size_t *content_len)
{
	char	quote;

	quote = 0;
	while (str[pos + len])
	{
		if ((str[pos + len] == '"' || str[pos + len] == '\'') && !quote)
			quote = str[pos + len];
		else if (quote && str[pos + len] == quote)
			quote = 0;
		else if (!quote && (ft_isspace(str[pos + len])
				|| isoperator(str[pos + len])))
			break ;
		else
			++(*content_len);
		++len;
	}
	return (len);
}

size_t	get_token_len(char *str, size_t pos, size_t *content_len)
{
	size_t	len;

	len = 0;
	*content_len = 0;
	if (isdoubleop(&str[pos]))
	{
		*content_len = 2;
		return (2);
	}
	if (isoperator(str[pos]))
	{
		*content_len = 1;
		return (1);
	}
	len += get_token_len_helper(str, pos, len, content_len);
	return (len);
}

int	fill_token(t_token *token, char *str, size_t *pos, int index)
{
	size_t	len;
	size_t	content_len;

	len = get_token_len(str, *pos, &content_len);
	token->index = index;
	token->content.len = content_len;
	token->content.ptr = create_token(str, *pos, len, content_len);
	if (!token->content.ptr)
		return (0);
	*pos += len;
	return (1);
}

int	init_tokens(t_token *tokens, char *str, size_t token_count)
{
	size_t	i;
	size_t	pos;

	i = 0;
	pos = 0;
	while (i < token_count)
	{
		pos += strskip(str + pos);
		if (!fill_token(&tokens[i], str, &pos, i))
		{
			free_tokens(tokens, token_count);
			return (0);
		}
		++i;
	}
	return (1);
}

int	tokenizing(char *str)
{
	t_token		*tokens;
	size_t		token_count;
	t_parser	*parser;
	t_ast_node	*ast;

	if (!str)
		return (0);
	token_count = count_token(str);
	tokens = ft_calloc((token_count + 1), sizeof(t_token));
	if (!tokens)
		return (0);
	if (!init_tokens(tokens, str, token_count))
		return (0);
	tokens[0].type = 1;
	for (int i = 0; tokens[i].content.ptr; i++)
	{
		printf("Token [%d] : content = {%s}, len = %zu, type = %d\n",
			i, tokens[i].content.ptr, tokens[i].content.len, tokens[i].type);
	}
	parser = malloc(sizeof(t_parser));
	ast = malloc(sizeof(t_ast_node));
	if (!ast || !parser)
		return (0);
	init_parser(parser, tokens, token_count);
	ast = parse_pipeline(parser);
	return (1);
}
