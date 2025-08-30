/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:14:51 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 11:23:38 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var(char *name, char **env)
{
	int		i;
	int		name_len;
	char	*value;

	if (!name || !env)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
		{
			value = env[i] + name_len + 1;
			return (value);
		}
		i++;
	}
	return (NULL);
}

static int	count_env_vars(char **env)
{
	int	count;

	count = 0;
	while (env[count])
		count++;
	return (count);
}

char	**copy_env(char **env)
{
	char	**new_env;
	int		count;
	int		i;

	if (!env)
		return (NULL);
	count = count_env_vars(env);
	new_env = safe_malloc(sizeof(char *) * (count + 1));
	i = 0;
	while (i < count)
	{
		new_env[i] = safe_strdup(env[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	set_env_var(char *name, char *value, t_shell *shell)
{
	char	*new_var;
	char	**new_env;
	int		count;
	int		i;

	if (!name || !value || !shell)
		return (1);
	new_var = create_env_string(name, value);
	if (env_var_exists(name, shell->env))
	{
		free (new_var);
		return (unset_env_var(name, shell) || set_env_var(name, value, shell));
	}
	count = count_env_vars(shell->env);
	new_env = safe_malloc(sizeof(char *) * (count + 2));
	i = -1;
	while (++i < count)
		new_env[i] = shell->env[i];
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
	return (0);
}
