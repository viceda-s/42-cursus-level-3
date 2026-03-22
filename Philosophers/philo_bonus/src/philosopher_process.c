/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/03/22 16:00:00 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	philosopher_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2);
	while (!simulation_ended())
	{
		take_forks(philo);
		eat(philo);
		drop_forks(philo);
		print_action(philo, MSG_SLEEP);
		ft_usleep(philo->data->time_to_sleep);
		print_action(philo, MSG_THINK);
	}
}
