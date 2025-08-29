/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:41:13 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 17:53:55 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_exit_code_expansion(int *i, t_shell *shell)
{
	char	*var_value;

	(*i)++;
	var_value = ft_itoa(shell->exit_code);
	return (var_value);
}

static char	*handle_variable_name(char *str, int *i, t_shell *shell)
{
	char	*var_name;
	char	*var_value;
	char	*temp;
	int		start;
	int		len;

	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	len = *i - start;
	if (len == 0)
		return (ft_strdup("$"));
	var_name = ft_substr(str, start, len);
	var_value = get_env_var(var_name, shell->env);
	if (var_value)
		temp = ft_strdup(var_value);
	else
		temp = ft_strdup("");
	free(var_name);
	return (temp);
}

static char	*handle_dollar_expansion(char *str, int *i, t_shell *shell)
{
	(*i)++;
	if (str[*i] == '?')
		return (handle_exit_code_expansion(i, shell));
	return (handle_variable_name(str, i, shell));
}

char	*process_char(char *str, int *i, t_shell *shell, t_expand_ctx *ctx)
{
	char	*result;
	char	*home;
	char	char_str[2];

	if (str[*i] == '$' && !ctx->in_single)
		return (handle_dollar_expansion(str, i, shell));
	else if (str[*i] == '~' && can_expand_tilde(str, *i, ctx))
	{
		home = get_env_var("HOME", shell->env);
		if (home)
			result = ft_strdup(home);
		else
			result = ft_strdup("~");
		(*i)++;
		return (result);
	}
	else
	{
		char_str[0] = str[*i];
		char_str[1] = '\0';
		result = ft_strdup(char_str);
		(*i)++;
		return (result);
	}
}

int	can_expand_tilde(char *str, int i, t_expand_ctx *ctx)
{
	if (ctx->in_single)
		return (0);
	if (i == 0 || str[i - 1] == ' ' || str[i - 1] == '\t' || str[i - 1] == ':')
	{
		if (!str[i + 1] || str[i + 1] == '/' || str[i + 1] == ' '
			|| str[i + 1] == '\t' || str[i + 1] == ':')
			return (1);
	}
	return (0);
}
