/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:27:37 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 10:27:38 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmd_equals(char *cmd, char *builtin)
{
	if (!cmd || !builtin)
		return (0);
	return (ft_strncmp(cmd, builtin, ft_strlen(builtin)) == 0
		&& ft_strlen(cmd) == ft_strlen(builtin));
}

int	is_builtin(char *cmd)

{
	if (!cmd)
		return (0);
	if (cmd_equals(cmd, "echo"))
		return (1);
	if (cmd_equals(cmd, "cd"))
		return (1);
	if (cmd_equals(cmd, "pwd"))
		return (1);
	if (cmd_equals(cmd, "export"))
		return (1);
	if (cmd_equals(cmd, "unset"))
		return (1);
	if (cmd_equals(cmd, "env"))
		return (1);
	if (cmd_equals(cmd, "exit"))
		return (1);
	return (0);
}

int	execute_builtin(char **args, t_shell *shell)

{
	if (!args || !args[0])
		return (1);
	if (cmd_equals(args[0], "echo"))
		return (builtin_echo(args));
	if (cmd_equals(args[0], "cd"))
		return (builtin_cd(args, shell));
	if (cmd_equals(args[0], "pwd"))
		return (builtin_pwd(args, shell));
	if (cmd_equals(args[0], "export"))
		return (builtin_export(args, shell));
	if (cmd_equals(args[0], "unset"))
		return (builtin_unset(args, shell));
	if (cmd_equals(args[0], "env"))
		return (builtin_env(shell));
	if (cmd_equals(args[0], "exit"))
		return (builtin_exit(args, shell));
	return (1);
}
