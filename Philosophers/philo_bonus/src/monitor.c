/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/03/22 16:00:00 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static int	check_death(t_table *table, long current_time)
{
	int	i;

	i = 0;
	while (i < table->data.nb_philo)
	{
		if (current_time - table->philos[i].last_meal_time
			> table->data.time_to_die)
		{
			print_action(&table->philos[i], MSG_DIED);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_meals_completed(t_table *table)
{
	int	i;

	if (table->data.nb_times_to_eat < 0)
		return (0);
	i = 0;
	while (i < table->data.nb_philo)
	{
		if (table->philos[i].meals_eaten < table->data.nb_times_to_eat)
			return (0);
		i++;
	}
	return (1);
}

void	monitor_routine(t_table *table)
{
	long	current_time;

	while (1)
	{
		usleep(1000);
		current_time = get_timestamp() - table->data.start_time;
		if (check_death(table, current_time))
			break ;
		if (check_meals_completed(table))
			break ;
	}
}
