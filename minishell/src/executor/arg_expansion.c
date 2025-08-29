/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:36:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 14:48:41 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args_filtered(char **args, int only_non_empty)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (args[i])
	{
		if (!only_non_empty || ft_strlen(args[i]) > 0)
			count++;
		i++;
	}
	return (count);
}

static void	copy_non_empty_args(char **expanded_args, char **filtered_args)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (expanded_args[i])
	{
		if (ft_strlen(expanded_args[i]) > 0)
		{
			filtered_args[j] = safe_strdup(expanded_args[i]);
			j++;
		}
		i++;
	}
	filtered_args[j] = NULL;
}

static char	**filter_empty_args(char **expanded_args)
{
	char	**filtered_args;
	int		filtered_count;

	filtered_count = count_args_filtered(expanded_args, 1);
	if (filtered_count == 0)
	{
		free_args(expanded_args);
		return (NULL);
	}
	filtered_args = safe_malloc(sizeof(char *) * (filtered_count + 1));
	copy_non_empty_args(expanded_args, filtered_args);
	free_args(expanded_args);
	return (filtered_args);
}

char	**expand_args(char **args, t_shell *shell)
{
	char	**expanded_args;
	int		count;
	int		i;

	if (!args)
		return (NULL);
	count = count_args_filtered(args, 0);
	expanded_args = safe_malloc(sizeof(char *) * (count + 1));
	i = 0;
	while (i < count)
	{
		expanded_args[i] = expand_variables(args[i], shell);
		if (!expanded_args[i])
			expanded_args[i] = safe_strdup("");
		i++;
	}
	expanded_args[i] = NULL;
	return (filter_empty_args(expanded_args));
}

void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
