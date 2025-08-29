/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolver.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:15:01 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 11:23:38 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path_dirs(char **env)
{
	char	*path_var;
	char	**paths;

	path_var = get_env_var("PATH", env);
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	return (paths);
}

static char	*try_path(char *path_dir, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(path_dir, "/");
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (access(full_path, F_OK | X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

char	*resolve_path(char *cmd, char **env)
{
	char	**paths;
	char	*full_path;
	int		i;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (safe_strdup(cmd));
	paths = get_path_dirs(env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = try_path(paths[i], cmd);
		if (full_path)
		{
			free_env(paths);
			return (full_path);
		}
		i++;
	}
	free_env(paths);
	return (NULL);
}
