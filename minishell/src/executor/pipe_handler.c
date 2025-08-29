/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:16:58 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 14:13:31 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_pipe(int pipefd[2], int is_last)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	(void)is_last;
}

static int	wait_pipe_processes(pid_t pid1, pid_t pid2)
{
	int	status1;
	int	status2;

	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFSIGNALED(status1) && WTERMSIG(status1) == SIGPIPE)
	{
		write(STDERR_FILENO, "Broken pipe\n", 12);
		return (128 + SIGPIPE);
	}
	if (WIFSIGNALED(status2) && WTERMSIG(status2) == SIGPIPE)
	{
		write(STDERR_FILENO, "Broken pipe\n", 12);
		return (128 + SIGPIPE);
	}
	return (WEXITSTATUS(status2));
}

static void	execute_left_pipe(t_ast *pipe_node, t_shell *shell, int pipefd[2])
{
	reset_signal_handlers();
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	exit(execute_ast(pipe_node->left, shell));
}

static void	execute_right_pipe(t_ast *pipe_node, t_shell *shell, int pipefd[2])
{
	reset_signal_handlers();
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	exit(execute_ast(pipe_node->right, shell));
}

int	execute_pipe(t_ast *pipe_node, t_shell *shell)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipefd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 == 0)
		execute_left_pipe(pipe_node, shell, pipefd);
	pid2 = fork();
	if (pid2 == 0)
		execute_right_pipe(pipe_node, shell, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	return (wait_pipe_processes(pid1, pid2));
}
