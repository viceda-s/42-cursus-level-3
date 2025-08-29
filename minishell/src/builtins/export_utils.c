/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:07:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 11:12:16 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_env_array(char **sorted)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (sorted[++i])
	{
		j = i;
		while (sorted[++j])
		{
			if (ft_strncmp(sorted[i], sorted[j], ft_strlen(sorted[i]) + 1) > 0)
			{
				tmp = sorted[i];
				sorted[i] = sorted[j];
				sorted[j] = tmp;
			}
		}
	}
}

void	print_sorted_env(char **env)
{
	char	**sorted;
	int		i;

	i = 0;
	while (env[i])
		i++;
	sorted = safe_malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (env[++i])
		sorted[i] = env[i];
	sorted[i] = NULL;
	sort_env_array(sorted);
	i = -1;
	while (sorted[++i])
		ft_printf("declare -x %s\n", sorted[i]);
	free(sorted);
}

int	handle_append_export(char *arg, char *plus_eq_pos, t_shell *shell)
{
	char	*name;
	char	*value;
	char	*existing_value;
	char	*new_value;

	name = ft_substr(arg, 0, plus_eq_pos - arg);
	value = plus_eq_pos + 2;
	existing_value = get_env_var(name, shell->env);
	if (existing_value)
	{
		new_value = ft_strjoin(existing_value, value);
		set_env_var(name, new_value, shell);
		free(new_value);
	}
	else
	{
		set_env_var(name, value, shell);
	}
	free(name);
	return (0);
}
