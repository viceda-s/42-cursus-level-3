/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpiovano <bpiovano@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:14:57 by viceda-s          #+#    #+#             */
/*   Updated: 2025/09/12 14:36:09 by bpiovano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_var_exists(char *name, char **env)
{
	int	i;
	int	name_len;

	if (!name || !env)
		return (0);
	name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*create_env_string(char *name, char *value)
{
	char	*env_str;
	char	*tmp;

	if (!name || !value)
		return (NULL);
	tmp = ft_strjoin(name, "=");
	if (!tmp)
		return (NULL);
	env_str = ft_strjoin(tmp, value);
	free(tmp);
	return (env_str);
}

void	free_env(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

static void	copy_env_entries(char **old_env, char **new_env, char *name,
		int count)
{
	int	i;
	int	j;
	int	name_len;

	name_len = ft_strlen(name);
	i = 0;
	j = 0;
	while (i < count)
	{
		if (ft_strncmp(old_env[i], name, name_len) == 0
			&& old_env[i][name_len] == '=')
		{
			free(old_env[i]);
		}
		else
		{
			new_env[j] = old_env[i];
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
}

int	unset_env_var(char *name, t_shell *shell)
{
	char	**new_env;
	int		count;

	if (!name || !shell || !shell->env)
		return (1);
	count = 0;
	while (shell->env[count])
		count++;
	new_env = safe_malloc(sizeof(char *) * count);
	copy_env_entries(shell->env, new_env, name, count);
	free(shell->env);
	shell->env = new_env;
	return (0);
}
