/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:18:48 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 10:26:10 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

// Forward declaration
typedef struct s_shell	t_shell;

/* ************************************************************************** */
/*                                 ENUMS                                      */
/* ************************************************************************** */

typedef enum e_ast_type
{
	AST_COMMAND,
	AST_PIPE,
	AST_REDIRECT,
	AST_SEMICOLON
}	t_ast_type;

/* ************************************************************************** */
/*                                STRUCTURES                                  */
/* ************************************************************************** */

typedef struct s_ast
{
	t_ast_type			type;
	char				**args;
	struct s_ast		*left;
	struct s_ast		*right;
	char				*redirect_file;
	t_token_type		redirect_type;
}	t_ast;

/* ************************************************************************** */
/*                             FUNCTION PROTOTYPES                           */
/* ************************************************************************** */

/* parser/parser.c */
t_ast	*parser(t_token *tokens, t_shell *shell);

/* parser/parse_utils.c */
int		is_redirect_token(t_token *token);
t_ast	*handle_leading_redirections(t_token **tokens, t_shell *shell);
t_ast	*parse_simple_command(t_token **tokens);
t_ast	*parse_command_args(t_token **tokens, t_shell *shell, t_ast *cmd_node);
t_ast	*handle_redirect_first(t_token **tokens, t_shell *shell);

/* parser/parse_helpers.c */
int		get_arg_count(char **args);
int		copy_existing_args(char **old_args, char **new_args, int count);
t_ast	*parse_redirection(t_token **tokens, t_shell *shell);
t_ast	*handle_command_first(t_token **tokens, t_shell *shell);

/* parser/ast_builder.c */
t_ast	*build_ast(t_token **tokens);
t_ast	*create_ast_node(t_ast_type type);

/* parser/syntax_checker.c */
int		check_syntax(t_token *tokens);
char	*check_syntax_and_get_error(t_token *tokens);
int		validate_redirections(t_token *tokens);

/* parser/syntax_utils.c */
int		is_redirect_type(t_token_type type);
char	*get_token_string(t_token_type type);
char	*check_pipe_syntax(t_token *current);
char	*check_semicolon_syntax(t_token *current);
char	*check_redirect_syntax(t_token *current);

/* parser/ast_utils.c */
void	free_ast(t_ast *ast);
void	print_ast(t_ast *ast, int depth);

#endif
