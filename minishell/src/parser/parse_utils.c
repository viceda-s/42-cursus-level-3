/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:05:57 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 10:19:31 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirect_token(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == TOKEN_REDIRECT_IN
		|| token->type == TOKEN_REDIRECT_OUT
		|| token->type == TOKEN_REDIRECT_APPEND
		|| token->type == TOKEN_HEREDOC);
}

t_ast	*handle_leading_redirections(t_token **tokens, t_shell *shell)
{
	t_ast	*redir_chain;
	t_ast	*redir;

	redir_chain = NULL;
	while (*tokens && is_redirect_token(*tokens))
	{
		redir = parse_redirection(tokens, shell);
		if (!redir)
			return (NULL);
		redir->left = redir_chain;
		redir_chain = redir;
	}
	return (redir_chain);
}

t_ast	*parse_simple_command(t_token **tokens)
{
	t_ast	*node;

	if (!*tokens || (*tokens)->type != TOKEN_WORD)
		return (NULL);
	node = create_ast_node(AST_COMMAND);
	node->args = safe_malloc(sizeof(char *) * 2);
	node->args[0] = safe_strdup((*tokens)->value);
	node->args[1] = NULL;
	*tokens = (*tokens)->next;
	return (node);
}

t_ast	*parse_command_args(t_token **tokens, t_shell *shell, t_ast *cmd_node)
{
	char	**new_args;
	int		current_count;
	int		i;

	(void)shell;
	if (!*tokens || (*tokens)->type != TOKEN_WORD)
		return (cmd_node);
	current_count = get_arg_count(cmd_node->args);
	new_args = safe_malloc(sizeof(char *) * (current_count + 2));
	i = copy_existing_args(cmd_node->args, new_args, current_count);
	new_args[i] = safe_strdup((*tokens)->value);
	new_args[i + 1] = NULL;
	if (cmd_node->args)
		free(cmd_node->args);
	cmd_node->args = new_args;
	*tokens = (*tokens)->next;
	return (cmd_node);
}

t_ast	*handle_redirect_first(t_token **tokens, t_shell *shell)
{
	t_ast	*cmd;
	t_ast	*redir;
	t_ast	*current;

	redir = handle_leading_redirections(tokens, shell);
	if (!redir)
		return (NULL);
	if (*tokens && (*tokens)->type == TOKEN_WORD)
	{
		cmd = parse_simple_command(tokens);
		if (!cmd)
			return (redir);
		current = redir;
		while (current->left)
			current = current->left;
		current->left = cmd;
	}
	return (redir);
}
