/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:19:01 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 14:48:22 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "parser.h"

/* Forward declarations */
typedef struct s_shell	t_shell;

/* ************************************************************************** */
/*                             FUNCTION PROTOTYPES                           */
/* ************************************************************************** */

/* executor/executor.c */
int		execute_ast(t_ast *ast, t_shell *shell);

/* executor/command_exec.c */
int		execute_command(t_ast *cmd, t_shell *shell);

/* executor/path_resolver.c */
char	*find_executable(char *cmd, char **env);

/* executor/arg_expansion.c */
char	**expand_args(char **args, t_shell *shell);
void	free_args(char **args);

/* executor/pipe_handler.c */
int		execute_pipe(t_ast *pipe_node, t_shell *shell);
void	setup_pipe(int pipefd[2], int is_last);

/* executor/redirect_handler.c */
int		setup_redirections(t_ast *node);

/* executor/redirect_utils.c */
int		validate_redir_file(t_ast *r);
int		count_redirections(t_ast *node);
void	fill_redir_list(t_ast *node, t_ast **redir_list, int count);

/* executor/heredoc.c */
int		create_heredoc(char *delimiter);
void	read_heredoc_input(int fd, char *delimiter);
int		handle_heredoc(char *delimiter);

/* executor/process_manager.c */
pid_t	create_process(void);
int		wait_for_processes(pid_t *pids, int count);

#endif
