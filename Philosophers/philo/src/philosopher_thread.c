/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_thread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/07/27 16:09:32 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philo == 1)
	{
		handle_single_philosopher(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!simulation_ended(philo))
	{
		take_forks(philo);
		eat(philo);
		drop_forks(philo);
		if (should_philosopher_stop(philo))
			break ;
		sleep_and_think(philo);
	}
	return (NULL);
}

int	should_philosopher_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	if (philo->data->nb_times_to_eat != -1
		&& philo->meals_eaten >= philo->data->nb_times_to_eat)
	{
		pthread_mutex_unlock(&philo->data->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (0);
}
