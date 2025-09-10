/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpiovano <bpiovano@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:06:11 by viceda-s          #+#    #+#             */
/*   Updated: 2025/09/10 18:16:57 by bpiovano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_indent(int depth)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		ft_printf(" ");
		i++;
	}
}

static void	print_command_args(char **args)
{
	int	i;

	if (args)
	{
		i = 0;
		while (args[i])
		{
			ft_printf("%s ", args[i]);
			i++;
		}
	}
}

static void	print_ast_type(t_ast *ast, int depth)
{
	if (ast->type == AST_COMMAND)
	{
		ft_printf("COMMAND: ");
		print_command_args(ast->args);
		ft_printf("\n");
	}
	else if (ast->type == AST_PIPE)
	{
		ft_printf("PIPE\n");
		print_ast(ast->left, depth + 1);
		print_ast(ast->right, depth + 1);
	}
	else if (ast->type == AST_SEMICOLON)
	{
		ft_printf("SEMICOLON\n");
		print_ast(ast->left, depth + 1);
		print_ast(ast->right, depth + 1);
	}
}

void	print_ast(t_ast *ast, int depth)
{
	if (!ast)
		return ;
	print_indent(depth);
	print_ast_type(ast, depth);
}
