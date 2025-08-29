/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:06:18 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 10:07:18 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*create_ast_node(t_ast_type type)
{
	t_ast	*node;

	node = safe_malloc(sizeof(t_ast));
	node->type = type;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	node->redirect_file = NULL;
	node->redirect_type = TOKEN_EOF;
	return (node);
}

t_ast	*build_ast(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	return (create_ast_node(AST_COMMAND));
}
