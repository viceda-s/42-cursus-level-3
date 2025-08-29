/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 09:55:58 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 10:06:37 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirect_type(t_token_type type)
{
	return (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_REDIRECT_APPEND || type == TOKEN_HEREDOC);
}

char	*get_token_string(t_token_type type)
{
	if (type == TOKEN_PIPE)
		return ("|");
	if (type == TOKEN_SEMICOLON)
		return (";");
	if (type == TOKEN_REDIRECT_IN)
		return ("<");
	if (type == TOKEN_REDIRECT_OUT)
		return (">");
	if (type == TOKEN_REDIRECT_APPEND)
		return (">>");
	if (type == TOKEN_HEREDOC)
		return ("<<");
	return ("newline");
}

char	*check_pipe_syntax(t_token *current)
{
	if (!current->next)
		return ("newline");
	if (current->next->type == TOKEN_PIPE
		|| current->next->type == TOKEN_SEMICOLON)
		return (get_token_string(current->next->type));
	return (NULL);
}

char	*check_semicolon_syntax(t_token *current)
{
	if (current->next && (current->next->type == TOKEN_PIPE
			|| current->next->type == TOKEN_SEMICOLON))
		return (get_token_string(current->next->type));
	return (NULL);
}

char	*check_redirect_syntax(t_token *current)
{
	if (!current->next)
		return ("newline");
	if (current->next->type != TOKEN_WORD)
		return (get_token_string(current->next->type));
	return (NULL);
}
