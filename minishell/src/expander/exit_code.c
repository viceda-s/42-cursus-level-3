/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:20:09 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 14:53:31 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_exit_code(t_shell *shell, int code)
{
	if (shell)
		shell->exit_code = code;
}

int	get_exit_code(t_shell *shell)
{
	if (!shell)
		return (0);
	return (shell->exit_code);
}
