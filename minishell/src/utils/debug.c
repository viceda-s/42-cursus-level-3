/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:24:32 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 11:33:38 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_type_names(char **type_names)
{
	type_names[0] = "WORD";
	type_names[1] = "PIPE";
	type_names[2] = "REDIRECT_IN";
	type_names[3] = "REDIRECT_OUT";
	type_names[4] = "REDIRECT_APPEND";
	type_names[5] = "HEREDOC";
	type_names[6] = "EOF";
}

static void	print_token_value(t_token *current, char **type_names)
{
	if (current->value && DEBUG_MODE)
		printf("Token: %s = '%s'\n",
			type_names[current->type], current->value);
	else if (DEBUG_MODE)
		printf("Token: %s = 'NULL'\n",
			type_names[current->type]);
}

void	debug_print_tokens(t_token *tokens)
{
	t_token	*current;
	char	*type_names[7];

	init_type_names(type_names);
	if (!tokens)
	{
		if (DEBUG_MODE)
			printf("No tokens to print\n");
		return ;
	}
	if (DEBUG_MODE)
		printf("=== TOKENS DEBUG ===\n");
	current = tokens;
	while (current)
	{
		print_token_value(current, type_names);
		current = current->next;
	}
	if (DEBUG_MODE)
		printf("=== END TOKENS ===\n");
}

void	debug_print_env(char **env)
{
	int	i;

	if (!env)
	{
		if (DEBUG_MODE)
			printf("No environment to print\n");
		return ;
	}
	if (DEBUG_MODE)
		printf("=== ENVIRONMENT DEBUG ===\n");
	i = 0;
	while (env[i])
	{
		if (DEBUG_MODE)
			printf("ENV[%d]: %s\n", i, env[i]);
		i++;
	}
	if (DEBUG_MODE)
		printf("=== END ENVIRONMENT ===\n");
}

void	debug_shell_state(t_shell *shell)
{
	if (!shell)
	{
		if (DEBUG_MODE)
			printf("Shell is NULL\n");
		return ;
	}
	if (DEBUG_MODE)
	{
		printf("=== SHELL STATE DEBUG ===\n");
		printf("Exit code: %d\n", shell->exit_code);
		printf("Interactive: %d\n", shell->interactive);
		printf("=== END SHELL STATE ===\n");
	}
}
