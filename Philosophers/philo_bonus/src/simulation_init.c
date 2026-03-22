/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/03/22 16:00:00 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	init_table(t_table *table)
{
	table->data.start_time = get_timestamp();
	table->data.simulation_end = 0;
	if (!init_semaphores(table))
		return (0);
	if (!init_philosophers(table))
		return (0);
	return (1);
}

int	init_philosophers(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->data.nb_philo);
	if (!table->philos)
		return (0);
	i = 0;
	while (i < table->data.nb_philo)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal_time = get_timestamp();
		table->philos[i].pid = -1;
		table->philos[i].data = &table->data;
		i++;
	}
	return (1);
}

void	start_simulation(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->data.nb_philo)
	{
		table->philos[i].pid = fork();
		if (table->philos[i].pid == -1)
			return ;
		if (table->philos[i].pid == 0)
		{
			philosopher_routine(&table->philos[i]);
			exit(0);
		}
		usleep(100);
	}
	table->monitor_pid = fork();
	if (table->monitor_pid == 0)
	{
		monitor_routine(table);
		exit(0);
	}
	i = -1;
	while (++i < table->data.nb_philo)
		waitpid(table->philos[i].pid, NULL, 0);
	waitpid(table->monitor_pid, NULL, 0);
}

void	cleanup_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data.nb_philo)
	{
		if (table->philos[i].pid > 0)
			kill(table->philos[i].pid, SIGTERM);
		i++;
	}
	if (table->monitor_pid > 0)
		kill(table->monitor_pid, SIGTERM);
	if (table->philos)
		free(table->philos);
	destroy_semaphores(table);
}
