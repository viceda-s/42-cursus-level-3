/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/07/29 15:59:37 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	cleanup_partial(t_table *table, int stage)
{
	if (stage >= 1 && table->philos)
		free(table->philos);
	if (stage >= 2 && table->forks)
		free(table->forks);
}

int	init_table(t_table *table)
{
	table->philos = malloc(sizeof(t_philo) * table->data.nb_philo);
	if (!table->philos)
	{
		printf("Error: Failed to allocate memory for philosophers\n");
		return (-1);
	}
	table->forks = malloc(sizeof(pthread_mutex_t) * table->data.nb_philo);
	if (!table->forks)
	{
		printf("Error: Failed to allocate memory for forks\n");
		cleanup_partial(table, 1);
		return (-1);
	}
	if (init_mutexes(table) == -1)
	{
		cleanup_partial(table, 2);
		return (-1);
	}
	if (init_philosophers(table) == -1)
	{
		cleanup_table(table);
		return (-1);
	}
	return (0);
}

int	init_philosophers(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data.nb_philo)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal_time = 0;
		table->philos[i].data = &table->data;
		table->philos[i].left_fork = &table->forks[i];
		if (table->data.nb_philo == 1)
			table->philos[i].right_fork = &table->forks[i];
		else
			table->philos[i].right_fork = &table->forks[(i + 1)
				% table->data.nb_philo];
		i++;
	}
	return (0);
}

void	start_simulation(t_table *table)
{
	int	i;

	table->data.start_time = get_timestamp();
	i = 0;
	while (i < table->data.nb_philo)
	{
		pthread_mutex_lock(&table->data.meal_mutex);
		table->philos[i].last_meal_time = table->data.start_time;
		pthread_mutex_unlock(&table->data.meal_mutex);
		pthread_create(&table->philos[i].thread, NULL,
			philosopher_routine, &table->philos[i]);
		i++;
	}
	pthread_create(&table->monitor, NULL, monitor_routine, table);
}

void	cleanup_table(t_table *table)
{
	if (table->philos)
	{
		free(table->philos);
		table->philos = NULL;
	}
	if (table->forks)
	{
		free(table->forks);
		table->forks = NULL;
	}
	destroy_all_mutexes(table);
}
