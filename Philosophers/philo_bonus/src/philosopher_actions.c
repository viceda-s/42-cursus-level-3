/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/03/22 16:00:00 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_action(philo, MSG_FORK);
	sem_wait(philo->data->forks);
	print_action(philo, MSG_FORK);
}

void	drop_forks(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	eat(t_philo *philo)
{
	print_action(philo, MSG_EAT);
	philo->last_meal_time = get_timestamp();
	philo->meals_eaten++;
	ft_usleep(philo->data->time_to_eat);
}
