/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpiovano <bpiovano@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:06:05 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/29 17:17:51 by bpiovano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_arg_count(char **args)
{
	int	count;

	count = 0;
	if (args)
	{
		while (args[count])
			count++;
	}
	return (count);
}

int	copy_existing_args(char **old_args, char **new_args, int count)
{
	int	i;

	i = 0;
	if (old_args)
	{
		while (i < count)
		{
			new_args[i] = old_args[i];
			i++;
		}
	}
	return (i);
}

t_ast	*parse_redirection(t_token **tokens, t_shell *shell)
{
	t_ast			*node;
	t_token_type	redir_type;

	if (!*tokens)
		return (NULL);
	if (!is_redirect_token(*tokens))
		return (NULL);
	redir_type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (!*tokens || (*tokens)->type != TOKEN_WORD)
		return (NULL);
	node = create_ast_node(AST_REDIRECT);
	node->redirect_type = redir_type;
	node->redirect_file = expand_variables((*tokens)->value, shell);
	if (!node->redirect_file)
		node->redirect_file = safe_strdup((*tokens)->value);
	*tokens = (*tokens)->next;
	return (node);
}

t_ast	*add_redir_to_chain(t_ast *redir, t_ast *redir_list, t_ast *cmd)
{
	if (!redir_list)
	{
		redir_list = redir;
		redir->left = cmd;
	}
	else
	{
		redir->left = redir_list;
		redir_list = redir;
	}
	return (redir_list);
}

t_ast	*handle_command_first(t_token **tokens, t_shell *shell)
{
	t_ast	*cmd;
	t_ast	*redir;
	t_ast	*redir_list;

	cmd = parse_simple_command(tokens);
	if (!cmd)
		return (NULL);
	redir_list = NULL;
	while (*tokens && ((*tokens)->type == TOKEN_WORD
			|| is_redirect_token(*tokens)))
	{
		if ((*tokens)->type == TOKEN_WORD)
			cmd = parse_command_args(tokens, shell, cmd);
		else
		{
			redir = parse_redirection(tokens, shell);
			if (!redir)
				break ;
			redir_list = add_redir_to_chain(redir, redir_list, cmd);
		}
	}
	if (redir_list)
		return (redir_list);
	return (cmd);
}
