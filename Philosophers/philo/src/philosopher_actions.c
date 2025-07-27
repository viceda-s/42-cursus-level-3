/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/07/27 16:09:59 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	get_fork_order(t_philo *philo, pthread_mutex_t **first,
	pthread_mutex_t **second)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	get_fork_order(philo, &first_fork, &second_fork);
	pthread_mutex_lock(first_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(second_fork);
	print_action(philo, "has taken a fork");
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	get_fork_order(philo, &first_fork, &second_fork);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

void	eat(t_philo *philo)
{
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_timestamp();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	ft_usleep(philo->data->time_to_eat);
}

void	sleep_and_think(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
	print_action(philo, "is thinking");
	if (philo->data->nb_philo % 2 == 1)
		ft_usleep(1);
}
