/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_thread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/07/29 16:02:57 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	should_stop_eating(t_philo *philo)
{
	int	should_stop;

	pthread_mutex_lock(&philo->data->meal_mutex);
	should_stop = (philo->data->nb_times_to_eat != -1
			&& philo->meals_eaten >= philo->data->nb_times_to_eat);
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (should_stop);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philo == 1)
	{
		print_action(philo, "has taken a fork");
		ft_usleep(philo->data->time_to_die);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!simulation_ended(philo))
	{
		take_forks(philo);
		eat(philo);
		drop_forks(philo);
		if (should_stop_eating(philo))
			break ;
		sleep_and_think(philo);
	}
	return (NULL);
}
