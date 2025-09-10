/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpiovano <bpiovano@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:27:31 by viceda-s          #+#    #+#             */
/*   Updated: 2025/09/10 16:40:23 by bpiovano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_pwd_vars(t_shell *shell, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (1);
	if (old_pwd)
		set_env_var("OLDPWD", old_pwd, shell);
	set_env_var("PWD", new_pwd, shell);
	free(new_pwd);
	return (0);
}

static char	*get_target_dir(char **args, t_shell *shell)
{
	char	*target;

	if (!args[1])
	{
		target = get_env_var("HOME", shell->env);
		if (!target)
		{
			error_msg("cd", NULL, "HOME not set");
			return (NULL);
		}
		return (target);
	}
	if (ft_strncmp(args[1], "-", 2) == 0 && ft_strlen(args[1]) == 1)
	{
		target = get_env_var("OLDPWD", shell->env);
		if (!target)
		{
			error_msg("cd", NULL, "OLDPWD not set");
			return (NULL);
		}
		return (target);
	}
	return (args[1]);
}

static int	check_cd_args(char **args)
{
	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd:", STDERR_FILENO);
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
		ft_putstr_fd("cd: hint: use quotes for ", STDERR_FILENO);
		ft_putstr_fd("directories with spaces\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	builtin_cd(char **args, t_shell *shell)
{
	char	*target;
	char	*old_pwd;
	int		is_dash;

	if (check_cd_args(args))
		return (1);
	old_pwd = getcwd(NULL, 0);
	is_dash = (args[1] && ft_strncmp(args[1], "-", 2) == 0
			&& ft_strlen(args[1]) == 1);
	target = get_target_dir(args, shell);
	if (!target)
	{
		free(old_pwd);
		return (1);
	}
	if (chdir(target) != 0)
	{
		error_msg("cd", NULL, "No such file or directory");
		free(old_pwd);
		return (1);
	}
	if (is_dash)
		ft_printf("%s\n", target);
	update_pwd_vars(shell, old_pwd);
	return (free(old_pwd), 0);
}
