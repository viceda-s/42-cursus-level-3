/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 05:33:55 by viceda-s          #+#    #+#             */
/*   Updated: 2025/07/27 16:49:58 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

// Cores ANSI para diferentes ações
# define COLOR_RESET	"\033[0m"
# define COLOR_FORK		"\033[33m"		// Amarelo para pegar garfo
# define COLOR_EAT		"\033[32m"		// Verde para comer
# define COLOR_SLEEP	"\033[36m"		// Ciano para dormir
# define COLOR_THINK	"\033[35m"		// Magenta para pensar
# define COLOR_DIED		"\033[31m"		// Vermelho para morte

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_times_to_eat;
	long			start_time;
	int				simulation_end;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_mutex;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

typedef struct s_table
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_t		monitor;
	t_data			data;
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
void	handle_single_philosopher(t_philo *philo);

/* mutex_manager.c */
int		init_mutexes(t_table *table);
int		init_data_mutexes(t_table *table);
int		init_fork_mutexes(t_table *table);

/* philosopher_thread.c */
void	*philosopher_routine(void *arg);
int		should_philosopher_stop(t_philo *philo);

/* philosopher_actions.c */
void	take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);
void	eat(t_philo *philo);
void	sleep_and_think(t_philo *philo);

/* simulation_monitor.c */
void	*monitor_routine(void *arg);
int		check_death(t_table *table);
int		check_meals_completed(t_table *table);
int		handle_death_detected(t_table *table, int i, long current_time);
void	end_simulation(t_table *table);

/* time_utils.c */
long	get_timestamp(void);
void	ft_usleep(long milliseconds);

/* simulation_utils.c */
void	print_action(t_philo *philo, char *action);
void	print_action_colored(t_philo *philo, char *action, char *color);
char	*get_action_color(char *action);
int		simulation_ended(t_philo *philo);
int		simulation_ended_unsafe(t_data *data);

#endif
