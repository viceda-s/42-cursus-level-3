/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpiovano <bpiovano@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:25:00 by bpiovano          #+#    #+#             */
/*   Updated: 2025/09/10 16:29:19 by bpiovano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
