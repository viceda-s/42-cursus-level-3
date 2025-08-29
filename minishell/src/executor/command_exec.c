/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpiovano <bpiovano@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:37:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/29 16:49:56 by bpiovano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

static int	execute_builtin_command(t_ast *cmd, t_shell *shell)
{
	char	**expanded_args;
	int		result;

	expanded_args = expand_args(cmd->args, shell);
	if (!expanded_args)
		return (1);
	result = execute_builtin(expanded_args, shell);
	free_args(expanded_args);
	return (result);
}

static int	fork_and_execute(char *executable, char **expanded_args,
		t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		reset_signal_handlers();
		if (execve(executable, expanded_args, shell->env) == -1)
		{
			perror("execve");
			exit(126);
		}
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	return (1);
}

static int	execute_external_command(t_ast *cmd, t_shell *shell)
{
	char		**expanded_args;
	char		*executable;
	struct stat	st;
	int			result;

	expanded_args = expand_args(cmd->args, shell);
	if (!expanded_args)
		return (1);
	executable = find_executable(expanded_args[0], shell->env);
	if (!executable)
		return (handle_exec_error(expanded_args, expanded_args[0]));
	if (stat(executable, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(expanded_args[0], STDERR_FILENO);
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
		free(executable);
		free_args(expanded_args);
		return (126);
	}
	result = fork_and_execute(executable, expanded_args, shell);
	free(executable);
	free_args(expanded_args);
	return (result);
}

int	execute_command(t_ast *cmd, t_shell *shell)
{
	char	**expanded_args;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	expanded_args = expand_args(cmd->args, shell);
	if (!expanded_args || !expanded_args[0] || !expanded_args[0][0])
	{
		if (expanded_args)
			free_args(expanded_args);
		return (0);
	}
	if (is_builtin(expanded_args[0]))
	{
		free_args(expanded_args);
		return (execute_builtin_command(cmd, shell));
	}
	free_args(expanded_args);
	return (execute_external_command(cmd, shell));
}
