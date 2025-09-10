/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpiovano <bpiovano@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:30:00 by bpiovano          #+#    #+#             */
/*   Updated: 2025/09/10 16:29:26 by bpiovano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_escape_char(char *input, int *i, char *result)
{
	char	char_str[2];

	(*i)++;
	char_str[0] = input[*i];
	char_str[1] = '\0';
	result = join_and_free(result, char_str);
	(*i)++;
	return (result);
}

static int	is_quote_char(char c)
{
	if (c == '\'')
		return (1);
	if (c == '"')
		return (1);
	return (0);
}

static char	*handle_regular_char(char *input, int *i, char *result)
{
	char	char_str[2];

	char_str[0] = input[*i];
	char_str[1] = '\0';
	result = join_and_free(result, char_str);
	(*i)++;
	return (result);
}

char	*extract_word(char *input, int *i)
{
	char	*result;

	result = ft_strdup("");
	while (input[*i])
	{
		if (is_word_delimiter(input[*i]))
			break ;
		if (is_quote_char(input[*i]))
			result = handle_quote_in_word(input, i, result);
		else if (input[*i] == '\\' && input[*i + 1])
			result = handle_escape_char(input, i, result);
		else
			result = handle_regular_char(input, i, result);
	}
	return (result);
}
