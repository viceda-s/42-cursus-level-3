/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpiovano <bpiovano@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:57:43 by viceda-s          #+#    #+#             */
/*   Updated: 2025/09/02 17:31:36 by bpiovano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_rainbow_prompt(void)
{
	char	*prompt_str;
	char	*temp;

	prompt_str = ft_strjoin(C_RED "k" C_ORANGE "i" C_YELLOW "t" C_GREEN "t",
			C_BLUE "y" C_VIOLET "s" C_RED "h" C_ORANGE "e");
	temp = ft_strjoin(prompt_str, C_YELLOW "l" C_GREEN "l" C_RESET "$ ");
	free(prompt_str);
	return (temp);
}

char	*get_prompt(t_shell *shell)
{
	char	*prompt;

	(void)shell;
	prompt = get_rainbow_prompt();
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
