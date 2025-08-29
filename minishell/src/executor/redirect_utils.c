/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:17:11 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 14:36:10 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_input_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror_msg(filename);
		return (1);
	}
	close(fd);
	return (0);
}

static int	validate_output_file(char *filename, int append)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		perror_msg(filename);
		return (1);
	}
	close(fd);
	return (0);
}

int	validate_redir_file(t_ast *r)
{
	if (!r->redirect_file)
		return (0);
	if (r->redirect_type == TOKEN_REDIRECT_IN)
		return (validate_input_file(r->redirect_file));
	else if (r->redirect_type == TOKEN_REDIRECT_OUT)
		return (validate_output_file(r->redirect_file, 0));
	else if (r->redirect_type == TOKEN_REDIRECT_APPEND)
		return (validate_output_file(r->redirect_file, 1));
	return (0);
}

int	count_redirections(t_ast *node)
{
	t_ast	*current;
	int		count;

	count = 0;
	current = node;
	while (current && current->type == AST_REDIRECT)
	{
		count++;
		current = current->left;
	}
	return (count);
}

void	fill_redir_list(t_ast *node, t_ast **redir_list, int count)
{
	t_ast	*current;
	int		i;

	i = 0;
	current = node;
	while (current && current->type == AST_REDIRECT && i < count)
	{
		redir_list[i++] = current;
		current = current->left;
	}
}
