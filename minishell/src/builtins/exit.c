/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:27:56 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 11:12:16 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>
#include <errno.h>

static int	is_numeric_and_valid(char *str)
{
	long long	result;
	int			i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '+' || str[i] == '-')
		return (0);
	if (!str[i])
		return (0);
	result = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		if (result > (LLONG_MAX - (str[i] - '0')) / 10)
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (1);
}

static int	has_internal_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (0);
		i++;
	}
	return (is_numeric_and_valid(str));
}

static int	is_numeric_with_quotes(char *str)
{
	char	*content;
	int		result;
	int		len;

	if (!str || !*str)
		return (0);
	len = ft_strlen(str);
	if (str[0] == '"' && str[len - 1] == '"' && len > 2)
	{
		content = ft_substr(str, 1, len - 2);
		result = is_numeric_and_valid(content);
		free(content);
		return (result);
	}
	if (str[0] == '\'' && str[len - 1] == '\'' && len > 2)
	{
		return (0);
	}
	return (has_internal_quotes(str));
}

static int	parse_exit_code(char *arg)
{
	char	*content;
	int		exit_code;

	if ((arg[0] == '"' && arg[ft_strlen(arg) - 1] == '"')
		|| (arg[0] == '\'' && arg[ft_strlen(arg) - 1] == '\''))
	{
		content = ft_substr(arg, 1, ft_strlen(arg) - 2);
		exit_code = ft_atoi(content);
		free(content);
	}
	else
		exit_code = ft_atoi(arg);
	return (exit_code);
}

int	builtin_exit(char **args, t_shell *shell)
{
	int	exit_code;

	ft_printf("exit\n");
	if (!args[1])
		cleanup_and_exit(shell, shell->exit_code);
	if (!is_numeric_with_quotes(args[1]) && !has_internal_quotes(args[1]))
	{
		error_msg("exit", args[1], "numeric argument required");
		cleanup_and_exit(shell, 2);
	}
	if (args[2])
	{
		error_msg("exit", NULL, "too many arguments");
		return (1);
	}
	exit_code = parse_exit_code(args[1]);
	cleanup_and_exit(shell, exit_code);
	return (0);
}
