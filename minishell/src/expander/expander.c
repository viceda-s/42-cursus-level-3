/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:19:45 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 17:56:07 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	toggle_quotes(char c, int *in_single, int *in_double)
{
	if (c == '\'' && !*in_double)
		*in_single = !*in_single;
	else if (c == '"' && !*in_single)
		*in_double = !*in_double;
}

static char	*handle_quote_char(char *str, int *i, t_expand_ctx *ctx)
{
	toggle_quotes(str[*i], &ctx->in_single, &ctx->in_double);
	(*i)++;
	return (NULL);
}

static char	*append_expanded_result(char *result, char *expanded)
{
	char	*temp;

	if (!expanded)
		return (result);
	temp = ft_strjoin(result, expanded);
	free(result);
	free(expanded);
	return (temp);
}

static char	*process_expansion_loop(char *str, t_shell *shell,
		t_expand_ctx *ctx)
{
	char	*result;
	char	*expanded;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if ((str[i] == '\'' && !ctx->in_double)
			|| (str[i] == '"' && !ctx->in_single))
		{
			handle_quote_char(str, &i, ctx);
			continue ;
		}
		expanded = process_char(str, &i, shell, ctx);
		result = append_expanded_result(result, expanded);
	}
	return (result);
}

char	*expand_variables(char *str, t_shell *shell)
{
	t_expand_ctx	ctx;

	if (!str || !shell)
		return (NULL);
	ctx.in_single = 0;
	ctx.in_double = 0;
	return (process_expansion_loop(str, shell, &ctx));
}
