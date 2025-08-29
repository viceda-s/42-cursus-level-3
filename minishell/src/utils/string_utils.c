/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:24:46 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 11:31:47 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

char	*trim_whitespace(char *str)
{
	char	*start;
	char	*end;
	int		len;
	char	*result;

	if (!str)
		return (NULL);
	start = str;
	while (*start && is_whitespace(*start))
		start++;
	if (!*start)
		return (ft_strdup(""));
	end = str + ft_strlen(str) - 1;
	while (end > start && is_whitespace(*end))
		end--;
	len = end - start + 1;
	result = safe_malloc(len + 1);
	ft_strlcpy(result, start, len + 1);
	return (result);
}

int	count_args(char **args)
{
	int	count;

	if (!args)
		return (0);
	count = 0;
	while (args[count])
		count++;
	return (count);
}
