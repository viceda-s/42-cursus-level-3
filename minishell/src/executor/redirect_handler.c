/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:17:11 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 14:38:35 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_input(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror_msg(filename);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		perror("dup2");
		return (1);
	}
	close(fd);
	return (0);
}

static int	redirect_output(char *filename, int append)
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
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		perror("dup2");
		return (1);
	}
	close(fd);
	return (0);
}

static int	process_redirections(t_ast **redir_list, int count,
		t_ast **last_input, t_ast **last_output)
{
	int	i;

	i = count - 1;
	while (i >= 0)
	{
		if (validate_redir_file(redir_list[i]) == 1)
			return (1);
		if (redir_list[i]->redirect_type == TOKEN_REDIRECT_IN
			|| redir_list[i]->redirect_type == TOKEN_HEREDOC)
			*last_input = redir_list[i];
		else if (redir_list[i]->redirect_type == TOKEN_REDIRECT_OUT
			|| redir_list[i]->redirect_type == TOKEN_REDIRECT_APPEND)
			*last_output = redir_list[i];
		i--;
	}
	return (0);
}

static int	apply_final_redirections(t_ast *last_input, t_ast *last_output)
{
	int	result;

	result = 0;
	if (last_input)
	{
		if (last_input->redirect_type == TOKEN_REDIRECT_IN)
			result = redirect_input(last_input->redirect_file);
		else if (last_input->redirect_type == TOKEN_HEREDOC)
			result = handle_heredoc(last_input->redirect_file);
		if (result != 0)
			return (result);
	}
	if (last_output)
	{
		if (last_output->redirect_type == TOKEN_REDIRECT_OUT)
			result = redirect_output(last_output->redirect_file, 0);
		else if (last_output->redirect_type == TOKEN_REDIRECT_APPEND)
			result = redirect_output(last_output->redirect_file, 1);
	}
	return (result);
}

int	setup_redirections(t_ast *node)
{
	t_ast	**redir_list;
	t_ast	*last_input;
	t_ast	*last_output;
	int		count;
	int		result;

	if (!node)
		return (0);
	count = count_redirections(node);
	if (count == 0)
		return (0);
	redir_list = (t_ast **)safe_malloc(sizeof(t_ast *) * count);
	fill_redir_list(node, redir_list, count);
	last_input = NULL;
	last_output = NULL;
	result = process_redirections(redir_list, count, &last_input, &last_output);
	if (result == 0)
		result = apply_final_redirections(last_input, last_output);
	free(redir_list);
	return (result);
}
