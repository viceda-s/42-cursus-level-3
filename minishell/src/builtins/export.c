/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:28:02 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 11:12:16 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_identifier_start(char *str)
{
	if (!str || !*str)
		return (0);
	if (str[0] == '=' || str[0] == '-')
		return (0);
	if (str[0] == '-' && str[1] == '-')
		return (0);
	if (ft_isdigit(str[0]))
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	return (1);
}

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!check_identifier_start(str))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			break ;
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static char	*find_plus_eq(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			return (&arg[i]);
		i++;
	}
	return (NULL);
}

static int	export_variable(char *arg, t_shell *shell)
{
	char	*name;
	char	*value;
	char	*eq_pos;
	char	*plus_eq_pos;

	if (!is_valid_identifier(arg))
	{
		error_msg("export", arg, "not a valid identifier");
		return (1);
	}
	plus_eq_pos = find_plus_eq(arg);
	if (plus_eq_pos)
		return (handle_append_export(arg, plus_eq_pos, shell));
	eq_pos = ft_strchr(arg, '=');
	if (!eq_pos)
		return (0);
	name = ft_substr(arg, 0, eq_pos - arg);
	value = eq_pos + 1;
	set_env_var(name, value, shell);
	free(name);
	return (0);
}

int	builtin_export(char **args, t_shell *shell)

{
	int	i;
	int	ret;

	if (!args[1])
	{
		print_sorted_env(shell->env);
		return (0);
	}
	ret = 0;
	i = 1;
	while (args[i])
	{
		if (export_variable(args[i], shell) != 0)
			ret = 1;
		i++;
	}
	return (ret);
}
