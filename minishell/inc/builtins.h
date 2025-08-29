/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:19:06 by viceda-s          #+#    #+#             */
/*   Updated: 2025/08/28 11:12:16 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/* Forward declarations */
typedef struct s_shell	t_shell;

/* ************************************************************************** */
/*                             FUNCTION PROTOTYPES                           */
/* ************************************************************************** */

/* builtins/builtin_handler.c */
int		is_builtin(char *cmd);
int		execute_builtin(char **args, t_shell *shell);

/* builtins/echo.c */
int		builtin_echo(char **args);

/* builtins/cd.c */
int		builtin_cd(char **args, t_shell *shell);

/* builtins/pwd.c */
int		builtin_pwd(char **args, t_shell *shell);

/* builtins/export.c */
int		builtin_export(char **args, t_shell *shell);

/* builtins/export_utils.c */
void	print_sorted_env(char **env);
int		handle_append_export(char *arg, char *plus_eq_pos, t_shell *shell);

/* builtins/unset.c */
int		builtin_unset(char **args, t_shell *shell);

/* builtins/env.c */
int		builtin_env(t_shell *shell);

/* builtins/exit.c */
int		builtin_exit(char **args, t_shell *shell);

/* environment/env_manager.c */
char	*get_env_var(char *name, char **env);
int		set_env_var(char *name, char *value, t_shell *shell);
int		unset_env_var(char *name, t_shell *shell);
char	**copy_env(char **env);

/* environment/env_utils.c */
int		env_var_exists(char *name, char **env);
char	*create_env_string(char *name, char *value);
void	free_env(char **env);

/* environment/path_resolver.c */
char	*resolve_path(char *cmd, char **env);
char	**get_path_dirs(char **env);

#endif
