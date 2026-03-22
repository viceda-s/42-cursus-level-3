/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/03/22 16:00:00 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <string.h>

# define COLOR_RESET	"\033[0m"
# define COLOR_FORK		"\033[33m"
# define COLOR_EAT		"\033[32m"
# define COLOR_SLEEP	"\033[36m"
# define COLOR_THINK	"\033[35m"
# define COLOR_DIED		"\033[31m"

# define EMOJI_FORK		"🍴"
# define EMOJI_EAT		"🍝"
# define EMOJI_SLEEP	"😴"
# define EMOJI_THINK	"🧠"
# define EMOJI_DIED		"💀"

# define MSG_FORK		"has taken a fork 🍴"
# define MSG_EAT		"is eating 🍝"
# define MSG_SLEEP		"is sleeping 😴"
# define MSG_THINK		"is thinking 🧠"
# define MSG_DIED		"died 💀"

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_times_to_eat;
	long			start_time;
	int				simulation_end;
	sem_t			*forks;
	sem_t			*write_sem;
	sem_t			*death_sem;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pid_t			pid;
	t_data			*data;
}	t_philo;

typedef struct s_table
{
	t_philo			*philos;
	t_data			data;
	pid_t			monitor_pid;
}	t_table;

/* main.c */
int		main(int argc, char **argv);

/* args_parser.c */
int		ft_atoi(const char *str);
int		parse_arguments(int argc, char **argv, t_data *data);
int		validate_arguments(t_data *data);

/* simulation_init.c */
int		init_table(t_table *table);
int		init_philosophers(t_table *table);
void	start_simulation(t_table *table);
void	cleanup_table(t_table *table);

/* semaphore_manager.c */
int		init_semaphores(t_table *table);
void	destroy_semaphores(t_table *table);

/* philosopher_process.c */
void	philosopher_routine(t_philo *philo);

/* philosopher_actions.c */
void	take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);
void	eat(t_philo *philo);
void	sleep_and_think(t_philo *philo);

/* monitor.c */
void	monitor_routine(t_table *table);

/* time_utils.c */
long	get_timestamp(void);
void	ft_usleep(long milliseconds);

/* simulation_utils.c */
void	print_action(t_philo *philo, const char *action);
int		simulation_ended(void);

#endif
