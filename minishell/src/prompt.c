/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:57:43 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 17:57:52 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt(t_shell *shell)
{
	char	*prompt;

	(void)shell;
	prompt = ft_strdup(PROMPT);
	return (prompt);
}

char	*read_input(t_shell *shell)
{
	char	*input;
	char	*prompt;

	prompt = get_prompt(shell);
	input = readline(prompt);
	free(prompt);
	if (input && *input)
		add_history(input);
	return (input);
}
