/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:20:17 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 14:58:47 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_token_value(t_token *token, t_shell *shell)
{
	char	*expanded;

	if (!token || !token->value || token->type != TOKEN_WORD)
		return ;
	expanded = expand_variables(token->value, shell);
	if (expanded)
	{
		free(token->value);
		token->value = expanded;
	}
}

void	expand_all_tokens(t_token *tokens, t_shell *shell)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		expand_token_value(current, shell);
		current = current->next;
	}
}
