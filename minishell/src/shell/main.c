/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpiovano <bpiovano@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:01:37 by viceda-s          #+#    #+#             */
/*   Updated: 2025/09/10 18:13:10 by bpiovano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_received = 0;

static int	process_input(char *input, t_shell *shell)
{
	t_token	*tokens;
	t_ast	*ast;
	int		exit_code;
	char	*error_token;

	if (!input || !*input)
		return (0);
	tokens = lexer(input);
	if (!tokens)
		return (0);
	error_token = check_syntax_and_get_error(tokens);
	if (error_token)
	{
		free_tokens(tokens);
		return (syntax_error(error_token));
	}
	ast = parser(tokens, shell);
	free_tokens(tokens);
	if (!ast)
		return (1);
	exit_code = execute_ast(ast, shell);
	free_ast(ast);
	shell->exit_code = exit_code;
	return (exit_code);
}

static int	handle_signal_interrupt(t_shell *shell, char *input)
{
	if (g_signal_received == SIGINT)
	{
		shell->exit_code = 130;
		g_signal_received = 0;
		if (input)
			free(input);
		return (1);
	}
	return (0);
}

static void	shell_loop(t_shell *shell)
{
	char	*input;
	char	*prompt;

	while (1)
	{
		prompt = get_prompt(shell);
		input = readline(prompt);
		free(prompt);
		if (handle_signal_interrupt(shell, input))
			continue ;
		if (!input)
		{
			ft_printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		process_input(input, shell);
		free(input);
	}
}

static int	handle_command_flag(int argc, char **argv, t_shell *shell)
{
	int	exit_status;

	if (argc >= 3 && ft_strncmp(argv[1], "-c", 2) == 0)
	{
		exit_status = process_input(argv[2], shell);
		cleanup_and_exit(shell, exit_status);
		return (exit_status);
	}
	return (-1);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	int		cmd_result;

	shell = init_shell(envp);
	if (!shell)
		return (EXIT_FAILURE);
	setup_signal_handlers();
	setup_terminal();
	cmd_result = handle_command_flag(argc, argv, shell);
	if (cmd_result != -1)
		return (cmd_result);
	if (isatty(STDIN_FILENO))
		shell->interactive = 1;
	shell_loop(shell);
	cleanup_and_exit(shell, shell->exit_code);
	return (shell->exit_code);
}
