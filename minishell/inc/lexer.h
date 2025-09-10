/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpiovano <bpiovano@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:18:56 by viceda-s          #+#    #+#             */
/*   Updated: 2025/09/10 16:38:51 by bpiovano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/* ************************************************************************** */
/*                                 ENUMS                                      */
/* ************************************************************************** */

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC,
	TOKEN_SEMICOLON,
	TOKEN_EOF
}	t_token_type;

/* ************************************************************************** */
/*                                STRUCTURES                                  */
/* ************************************************************************** */

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}	t_token;

/* ************************************************************************** */
/*                             FUNCTION PROTOTYPES                           */
/* ************************************************************************** */

/* lexer/lexer.c */
t_token	*lexer(char *input);

/* lexer/tokenizer.c */
t_token	*tokenize_input(char *input);

/* lexer/tokenizer_utils.c */
char	*join_and_free(char *s1, char *s2);
int		is_word_delimiter(char c);

/* lexer/escape_handler.c */
char	*process_quoted_content(char *content, char quote_char);
char	*extract_quoted_content(char *input, int *i, char quote_char);
char	*handle_quote_in_word(char *input, int *i, char *result);

/* lexer/word_builder.c */
char	*extract_word(char *input, int *i);

/* lexer/token_utils.c */
void	add_token(t_token **head, t_token *new_token);
void	free_tokens(t_token *tokens);
void	print_tokens(t_token *tokens);
t_token	*create_token(t_token_type type, char *value);

/* lexer/quote_handler.c */
char	*handle_quotes(char *input, int *i);
int		is_quote(char c);
int		count_quotes(char *str, char quote);
int		has_unclosed_quotes(char *input);

#endif
