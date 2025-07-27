/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_monitor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/07/27 16:52:05 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*monitor_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (!simulation_ended_unsafe(&table->data))
	{
		if (check_death(table) == 1)
			break ;
		if (check_meals_completed(table) == 1)
		{
			end_simulation(table);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}

int	check_death(t_table *table)
{
	int		i;
	long	current_time;
	long	last_meal;

	i = 0;
	current_time = get_timestamp();
	while (i < table->data.nb_philo)
	{
		pthread_mutex_lock(&table->data.meal_mutex);
		last_meal = table->philos[i].last_meal_time;
		pthread_mutex_unlock(&table->data.meal_mutex);
		if (simulation_ended_unsafe(&table->data))
			return (0);
		if ((current_time - last_meal) >= table->data.time_to_die)
			return (handle_death_detected(table, i, current_time));
		i++;
	}
	return (0);
}

int	check_meals_completed(t_table *table)
{
	int	i;
	int	completed_meals;

	if (table->data.nb_times_to_eat == -1)
		return (0);
	pthread_mutex_lock(&table->data.meal_mutex);
	completed_meals = 0;
	i = 0;
	while (i < table->data.nb_philo)
	{
		if (table->philos[i].meals_eaten >= table->data.nb_times_to_eat)
			completed_meals++;
		i++;
	}
	pthread_mutex_unlock(&table->data.meal_mutex);
	return (completed_meals == table->data.nb_philo);
}

int	handle_death_detected(t_table *table, int i, long current_time)
{
	long	timestamp;

	pthread_mutex_lock(&table->data.death_mutex);
	if (!table->data.simulation_end)
	{
		table->data.simulation_end = 1;
		pthread_mutex_unlock(&table->data.death_mutex);
		pthread_mutex_lock(&table->data.write_mutex);
		timestamp = current_time - table->data.start_time;
		printf("%s%ld %d died%s\n", COLOR_DIED, timestamp,
			table->philos[i].id, COLOR_RESET);
		pthread_mutex_unlock(&table->data.write_mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->data.death_mutex);
	return (0);
}

void	end_simulation(t_table *table)
{
	pthread_mutex_lock(&table->data.death_mutex);
	table->data.simulation_end = 1;
	pthread_mutex_unlock(&table->data.death_mutex);
}
