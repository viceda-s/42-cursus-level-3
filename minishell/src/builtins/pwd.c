/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:28:10 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 10:55:49 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

static int	check_pwd_validity(char *pwd_env, char *cwd)
{
	struct stat	pwd_stat;
	struct stat	cwd_stat;

	if (!cwd || stat(pwd_env, &pwd_stat) != 0 || stat(cwd, &cwd_stat) != 0)
		return (0);
	if (pwd_stat.st_ino == cwd_stat.st_ino
		&& pwd_stat.st_dev == cwd_stat.st_dev)
		return (1);
	return (0);
}

static int	try_pwd_env(t_shell *shell)
{
	char	*pwd_env;
	char	*cwd;

	pwd_env = get_env_var("PWD", shell->env);
	if (!pwd_env)
		return (0);
	cwd = getcwd(NULL, 0);
	if (check_pwd_validity(pwd_env, cwd))
	{
		ft_printf("%s\n", pwd_env);
		free(cwd);
		return (1);
	}
	if (cwd)
		free(cwd);
	return (0);
}

int	builtin_pwd(char **args, t_shell *shell)
{
	char	*cwd;

	(void)args;
	if (try_pwd_env(shell))
		return (0);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	ft_printf("%s\n", cwd);
	free(cwd);
	return (0);
}
