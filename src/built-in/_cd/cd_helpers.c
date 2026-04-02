/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 14:45:53 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/02 15:12:16 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//fetch $HOME from env
static char	*resolve_home(t_ctx *ctx)
{
	char	*target;

	target = ft_getenv(ctx->env, "HOME");
	if (!target)
		builtin_error("cd", NULL, "HOME not set");
	return (target);
}

//fetch $OLDPWD and print it
static char	*resolve_oldpwd(t_ctx *ctx)
{
	char	*target;

	target = ft_getenv(ctx->env, "OLDPWD");
	if (!target)
	{
		builtin_error("cd", NULL, "OLDPWD not set");
		return (NULL);
	}
	ft_putendl_fd(target, STDOUT_FILENO);
	return (target);
}

//Fetch the arg for cd and activate a must_free flag
static char	*resolve_arg(t_token *tokens, int *must_free)
{
	char	*arg;

	arg = ft_substr(tokens[1].content.ptr, 0, tokens[1].content.len);
	if (!arg)
		return (NULL);
	*must_free = 1;
	return (arg);
}

//Handle ~ and - arg for cd
static char	*resolve_tilde_or_dash(char *arg, t_ctx *ctx)
{
	if (ft_strcmp(arg, "~") == 0)
	{
		free(arg);
		return (resolve_home(ctx));
	}
	if (ft_strcmp(arg, "-") == 0)
	{
		free(arg);
		return (resolve_oldpwd(ctx));
	}
	return (arg);
}

//handle no arg hypothesis, call previous functions, 
//set must_free flag to 0 if it was a tilde or dash arg
char	*resolve_target(t_token *tokens, int token_count, t_ctx *ctx,
				int *must_free)
{
	char	*arg;
	char	*target;

	*must_free = 0;
	if (token_count == 1)
	{
		arg = resolve_home(ctx);
		return (arg);
	}
	arg = resolve_arg(tokens, must_free);
	if (!arg)
		return (NULL);
	target = resolve_tilde_or_dash(arg, ctx);
	if (target != arg)
		*must_free = 0;
	return (target);
}
