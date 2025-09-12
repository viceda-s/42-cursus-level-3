/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpiovano <bpiovano@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:47:35 by bpiovano          #+#    #+#             */
/*   Updated: 2025/09/12 14:21:00 by bpiovano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_path_error(char **expanded_args, char *cmd_name)
{
	struct stat	st;

	if (access(cmd_name, F_OK) == 0)
	{
		if (stat(cmd_name, &st) == 0 && S_ISDIR(st.st_mode))
		{
			ft_putendl_fd(": Is a directory", STDERR_FILENO);
			free_args(expanded_args);
			return (126);
		}
		else if (access(cmd_name, X_OK) != 0)
		{
			ft_putendl_fd(": Permission denied", STDERR_FILENO);
			free_args(expanded_args);
			return (126);
		}
	}
	else
	{
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		free_args(expanded_args);
		return (127);
	}
	return (0);
}

int	handle_exec_error(char **expanded_args, char *cmd_name)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	if (ft_strchr(cmd_name, '/'))
		return (handle_path_error(expanded_args, cmd_name));
	ft_putendl_fd(": command not found", STDERR_FILENO);
	free_args(expanded_args);
	return (127);
}
