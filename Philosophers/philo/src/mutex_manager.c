/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/07/29 15:59:37 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_mutexes(t_table *table)
{
	if (init_data_mutexes(table) == -1)
		return (-1);
	if (init_fork_mutexes(table) == -1)
		return (-1);
	return (0);
}

int	init_data_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->data.write_mutex, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&table->data.death_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&table->data.write_mutex);
		return (-1);
	}
	if (pthread_mutex_init(&table->data.meal_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&table->data.write_mutex);
		pthread_mutex_destroy(&table->data.death_mutex);
		return (-1);
	}
	return (0);
}

int	init_fork_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data.nb_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->forks[i]);
			destroy_data_mutexes(table);
			return (-1);
		}
		i++;
	}
	return (0);
}

void	destroy_data_mutexes(t_table *table)
{
	pthread_mutex_destroy(&table->data.write_mutex);
	pthread_mutex_destroy(&table->data.death_mutex);
	pthread_mutex_destroy(&table->data.meal_mutex);
}

void	destroy_all_mutexes(t_table *table)
{
	int	i;

	if (table->forks)
	{
		i = 0;
		while (i < table->data.nb_philo)
			pthread_mutex_destroy(&table->forks[i++]);
	}
	destroy_data_mutexes(table);
}
