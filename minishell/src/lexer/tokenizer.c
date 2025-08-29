/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:45:12 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 14:09:21 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	get_redirect_type(char *str, int *i)
{
	if (str[*i] == '<' && str[*i + 1] == '<')
	{
		*i += 2;
		return (TOKEN_HEREDOC);
	}
	if (str[*i] == '<')
	{
		(*i)++;
		return (TOKEN_REDIRECT_IN);
	}
	if (str[*i] == '>' && str[*i + 1] == '>')
	{
		*i += 2;
		return (TOKEN_REDIRECT_APPEND);
	}
	if (str[*i] == '>')
	{
		(*i)++;
		return (TOKEN_REDIRECT_OUT);
	}
	return (TOKEN_WORD);
}

static t_token_type	get_token_type(char *str, int *i)
{
	if (str[*i] == '|')
	{
		(*i)++;
		return (TOKEN_PIPE);
	}
	if (str[*i] == ';')
	{
		(*i)++;
		return (TOKEN_SEMICOLON);
	}
	return (get_redirect_type(str, i));
}

t_token	*tokenize_input(char *input)
{
	t_token			*head;
	t_token			*current;
	t_token_type	type;
	char			*value;
	int				i;

	head = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			i++;
		if (!input[i])
			break ;
		type = get_token_type(input, &i);
		if (type != TOKEN_WORD)
			value = NULL;
		else
			value = extract_word(input, &i);
		current = create_token(type, value);
		add_token(&head, current);
	}
	return (head);
}
