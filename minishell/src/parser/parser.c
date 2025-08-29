/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:06:28 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 10:19:31 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast	*parse_expression(t_token **tokens, t_shell *shell);
static t_ast	*parse_pipeline(t_token **tokens, t_shell *shell);
static t_ast	*parse_pipeline_element(t_token **tokens, t_shell *shell);

t_ast	*parser(t_token *tokens, t_shell *shell)
{
	t_token	*current;
	t_ast	*ast;

	if (!tokens)
		return (NULL);
	current = tokens;
	ast = parse_expression(&current, shell);
	return (ast);
}

static t_ast	*parse_expression(t_token **tokens, t_shell *shell)
{
	t_ast	*left;
	t_ast	*node;

	left = parse_pipeline(tokens, shell);
	if (!left)
		return (NULL);
	while (*tokens && (*tokens)->type == TOKEN_SEMICOLON)
	{
		*tokens = (*tokens)->next;
		node = create_ast_node(AST_SEMICOLON);
		node->left = left;
		node->right = parse_pipeline(tokens, shell);
		left = node;
	}
	return (left);
}

static t_ast	*parse_pipeline(t_token **tokens, t_shell *shell)
{
	t_ast	*left;
	t_ast	*node;

	left = parse_pipeline_element(tokens, shell);
	if (!left)
		return (NULL);
	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		*tokens = (*tokens)->next;
		node = create_ast_node(AST_PIPE);
		node->left = left;
		node->right = parse_pipeline_element(tokens, shell);
		left = node;
	}
	return (left);
}

static t_ast	*parse_pipeline_element(t_token **tokens, t_shell *shell)
{
	if (*tokens && is_redirect_token(*tokens))
		return (handle_redirect_first(tokens, shell));
	if (*tokens && (*tokens)->type == TOKEN_WORD)
		return (handle_command_first(tokens, shell));
	return (NULL);
}
