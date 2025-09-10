/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_validator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpiovano <bpiovano@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:15:00 by bpiovano          #+#    #+#             */
/*   Updated: 2025/09/10 18:16:58 by bpiovano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes_in_ast(t_ast *ast)
{
	int	count;

	if (!ast)
		return (0);
	count = 0;
	if (ast->type == AST_PIPE)
		count = 1;
	count += count_pipes_in_ast(ast->left);
	count += count_pipes_in_ast(ast->right);
	return (count);
}

int	validate_pipe_limit(t_ast *ast)
{
	int	pipe_count;

	if (!ast)
		return (1);
	pipe_count = count_pipes_in_ast(ast);
	if (pipe_count > MAX_PIPES)
	{
		ft_printf("minishell: too many pipes (limit: %d)\n", MAX_PIPES);
		return (0);
	}
	return (1);
}
