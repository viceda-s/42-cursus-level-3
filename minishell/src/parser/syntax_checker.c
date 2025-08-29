/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 09:54:43 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 10:19:29 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*process_token_syntax(t_token *current, t_token *prev)
{
	char	*error;

	if (current->type == TOKEN_PIPE)
	{
		error = check_pipe_syntax(current);
		if (error)
			return (error);
	}
	if (current->type == TOKEN_SEMICOLON)
	{
		error = check_semicolon_syntax(current);
		if (error)
			return (error);
	}
	if (is_redirect_type(current->type))
	{
		error = check_redirect_syntax(current);
		if (error)
			return (error);
	}
	if (prev && is_redirect_type(prev->type)
		&& is_redirect_type(current->type))
		return (get_token_string(current->type));
	return (NULL);
}

char	*check_syntax_and_get_error(t_token *tokens)
{
	t_token	*current;
	t_token	*prev;
	char	*error;

	if (!tokens)
		return (NULL);
	current = tokens;
	prev = NULL;
	if (current->type == TOKEN_PIPE || current->type == TOKEN_SEMICOLON)
		return (get_token_string(current->type));
	while (current)
	{
		error = process_token_syntax(current, prev);
		if (error)
			return (error);
		prev = current;
		current = current->next;
	}
	if (prev && (prev->type == TOKEN_PIPE || is_redirect_type(prev->type)))
		return ("newline");
	return (NULL);
}

int	check_syntax(t_token *tokens)
{
	return (check_syntax_and_get_error(tokens) == NULL);
}

int	validate_redirections(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (is_redirect_type(current->type))
		{
			if (!current->next || current->next->type != TOKEN_WORD)
				return (0);
		}
		current = current->next;
	}
	return (1);
}
