/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpiovano <bpiovano@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:18:38 by viceda-s          #+#    #+#             */
/*   Updated: 2025/09/01 18:27:22 by bpiovano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*                                 INCLUDES                                   */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/include/libft.h"
# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "builtins.h"

/* ************************************************************************** */
/*                                 DEFINES                                    */
/* ************************************************************************** */

# define MAX_PATH 4096
# define MAX_CMD_LEN 4096

// Colores ANSI para el arcoíris
#define C_RED     "\033[91m"
#define C_ORANGE  "\033[38;5;208m"
#define C_YELLOW  "\033[93m"
#define C_GREEN   "\033[92m"
#define C_BLUE    "\033[94m"
#define C_INDIGO  "\033[38;5;54m"
#define C_VIOLET  "\033[95m"
#define C_RESET   "\033[0m"

/* Códigos de saída */
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_MISUSE 2
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_CMD_NOT_EXECUTABLE 126

/* Estados dos processos */
# define PROCESS_RUNNING 1
# define PROCESS_STOPPED 2
# define PROCESS_DONE 3

/* Debug mode */
# ifdef DEBUG
#  define DEBUG_MODE 1
# else
#  define DEBUG_MODE 0
# endif

/* ************************************************************************** */
/*                                STRUCTURES                                  */
/* ************************************************************************** */

/* Variável global para sinais (única permitida) */
extern int	g_signal_received;

/* Estrutura para contexto de expansão */
typedef struct s_expand_ctx
{
	int		in_single;
	int		in_double;
}	t_expand_ctx;

/* Estrutura principal da shell */
typedef struct s_shell
{
	char			**env;			/* Variáveis de ambiente */
	int				exit_code;		/* Código de saída do último comando */
	int				interactive;	/* Modo interativo */
	struct s_token	*tokens;		/* Lista de tokens */
	struct s_ast	*ast;			/* Árvore sintática */
}	t_shell;

/* ************************************************************************** */
/*                             FUNÇÃO PROTOTYPES                             */
/* ************************************************************************** */

/* main.c */
int		main(int argc, char **argv, char **envp);

/* init.c */
t_shell	*init_shell(char **envp);
int		setup_signals(void);
void	setup_terminal(void);

/* prompt.c */
char	*get_prompt(t_shell *shell);
char	*read_input(t_shell *shell);

/* signals.c */
void	signal_handler(int sig);
void	setup_signal_handlers(void);
void	reset_signal_handlers(void);

/* cleanup.c */
void	cleanup_shell(t_shell *shell);
void	free_tokens(struct s_token *tokens);
void	free_ast(struct s_ast *ast);
void	cleanup_and_exit(t_shell *shell, int exit_code);

/* utils.c */
void	error_msg(char *cmd, char *arg, char *msg);
void	perror_msg(char *cmd);
int		syntax_error(char *token);
void	*safe_malloc(size_t size);
char	*safe_strdup(const char *s);
void	safe_free(void **ptr);
int		is_whitespace(char c);
char	*trim_whitespace(char *str);
int		count_args(char **args);

/* expander/expander.c */
char	*expand_variables(char *str, t_shell *shell);

/* expander/expander_utils.c */
char	*append_char_to_result(char *result, char c);
char	*handle_tilde_expansion(char *str, int *i, t_shell *shell,
			char *result);
char	*handle_variable_expansion(char *str, int *i, t_shell *shell,
			char *result);

/* expander/expander_helpers.c */
char	*process_char(char *str, int *i, t_shell *shell, t_expand_ctx *ctx);
int		can_expand_tilde(char *str, int i, t_expand_ctx *ctx);

#endif
