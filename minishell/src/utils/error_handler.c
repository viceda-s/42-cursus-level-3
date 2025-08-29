/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:24:17 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 11:24:22 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *str)
{
	if (str)
		write(STDERR_FILENO, str, ft_strlen(str));
}

void	print_error_nl(char *str)
{
	print_error(str);
	write(STDERR_FILENO, "\n", 1);
}

int	handle_error(char *context, char *message, int exit_code)
{
	if (context)
	{
		print_error("minishell: ");
		print_error(context);
		print_error(": ");
	}
	if (message)
		print_error_nl(message);
	return (exit_code);
}
