/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:04:17 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 14:09:21 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_and_free(char *s1, char *s2)
{
	char	*result;

	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

char	*process_quoted_content(char *content, char quote_char)
{
	char	*marked;
	char	*temp;

	if (quote_char == '"')
	{
		marked = ft_strjoin("\"", content);
		temp = ft_strjoin(marked, "\"");
		free(marked);
		return (temp);
	}
	else if (quote_char == '\'')
	{
		marked = ft_strjoin("'", content);
		temp = ft_strjoin(marked, "'");
		free(marked);
		return (temp);
	}
	return (ft_strdup(content));
}

char	*extract_quoted_content(char *input, int *i, char quote_char)
{
	int		quote_start;
	int		len;
	char	*content;

	(*i)++;
	quote_start = *i;
	while (input[*i] && input[*i] != quote_char)
		(*i)++;
	if (input[*i] != quote_char)
		return (NULL);
	len = *i - quote_start;
	if (len == 0)
		content = ft_strdup("");
	else
		content = ft_substr(input, quote_start, len);
	(*i)++;
	return (content);
}

char	*handle_quote_in_word(char *input, int *i, char *result)
{
	char	quote_char;
	char	*quoted_content;
	char	*processed_content;

	quote_char = input[*i];
	quoted_content = extract_quoted_content(input, i, quote_char);
	if (!quoted_content)
		return (result);
	processed_content = process_quoted_content(quoted_content, quote_char);
	free(quoted_content);
	result = join_and_free(result, processed_content);
	free(processed_content);
	return (result);
}

char	*extract_word(char *input, int *i)
{
	char	*result;
	char	char_str[2];

	result = ft_strdup("");
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t'
		&& input[*i] != '|' && input[*i] != '<' && input[*i] != '>'
		&& input[*i] != ';')
	{
		if (input[*i] == '\'' || input[*i] == '"')
			result = handle_quote_in_word(input, i, result);
		else
		{
			char_str[0] = input[*i];
			char_str[1] = '\0';
			result = join_and_free(result, char_str);
			(*i)++;
		}
	}
	return (result);
}
