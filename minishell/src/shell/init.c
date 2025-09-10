/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpiovano <bpiovano@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:58:54 by viceda-s          #+#    #+#             */
/*   Updated: 2025/09/10 13:26:22 by bpiovano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_env_vars(t_shell *shell)
{
	char	*shlvl;
	char	*new_shlvl;
	int		level;

	shlvl = get_env_var("SHLVL", shell->env);
	if (shlvl)
	{
		level = ft_atoi(shlvl) + 1;
		new_shlvl = ft_itoa(level);
		set_env_var("SHLVL", new_shlvl, shell);
		free(new_shlvl);
	}
	else
		set_env_var("SHLVL", "1", shell);
}

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = safe_malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = copy_env(envp);
	if (!shell->env)
	{
		free(shell);
		return (NULL);
	}
	shell->exit_code = 0;
	shell->interactive = 0;
	shell->tokens = NULL;
	shell->ast = NULL;
	init_env_vars(shell);
	return (shell);
}

int	setup_signals(void)
{
	return (0);
}

void	setup_terminal(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return ;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
