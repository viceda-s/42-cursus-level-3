/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:16:43 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 14:12:22 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_redirect(t_ast *ast, t_shell *shell)
{
	int		saved_stdin;
	int		saved_stdout;
	int		result;
	t_ast	*command_node;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (setup_redirections(ast) != 0)
	{
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
	command_node = ast;
	while (command_node && command_node->type == AST_REDIRECT)
		command_node = command_node->left;
	result = execute_ast(command_node, shell);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (result);
}

int	execute_ast(t_ast *ast, t_shell *shell)
{
	int	exit_code;

	if (!ast || !shell)
		return (1);
	if (ast->type == AST_PIPE)
		return (execute_pipe(ast, shell));
	else if (ast->type == AST_COMMAND)
		return (execute_command(ast, shell));
	else if (ast->type == AST_REDIRECT)
		return (execute_redirect(ast, shell));
	else if (ast->type == AST_SEMICOLON)
	{
		exit_code = execute_ast(ast->left, shell);
		shell->exit_code = exit_code;
		return (execute_ast(ast->right, shell));
	}
	return (1);
}
