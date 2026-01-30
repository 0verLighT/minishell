/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 02:31:28 by jdessoli          #+#    #+#             */
/*   Updated: 2026/01/26 02:45:06 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

//Allows to take chunks of the input,
//with a precise starting and ending point
typedef struct slice
{
	char	*ptr;
	int		len;
}	t_slice;

//A token is a chunk of the input with an index
//That way, we can work on isolated chunks by giving the index
typedef struct token
{
	int		index;
	t_slice	content;
}	t_token;

//tokenizer_utils.c
int		is_space(char c);
int		strskip(char *str, char *charset);
int		strfind(char *str, char *charset);
int		count_token(char *str);
t_slice	*token_maker(char *str);

//tokenizer_utils_two.c
int		get_token_len(char *str, int pos);
int		fill_token(t_token *token, char *str, int pos, int index);
void	init_sentinel(t_token *token);
int		process_tokens(t_token *tokens, char *str, int token_count);
t_token	*tokenizing(char *str);

//tokenizer_utils_three.c
void	free_tokens(t_token *tokens);
