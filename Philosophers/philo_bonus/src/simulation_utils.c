/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/03/22 16:00:00 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	print_action(t_philo *philo, const char *action)
{
	long			timestamp;
	const char		*color;

	color = COLOR_RESET;
	if (!strcmp(action, MSG_FORK))
		color = COLOR_FORK;
	else if (!strcmp(action, MSG_EAT))
		color = COLOR_EAT;
	else if (!strcmp(action, MSG_SLEEP))
		color = COLOR_SLEEP;
	else if (!strcmp(action, MSG_THINK))
		color = COLOR_THINK;
	else if (!strcmp(action, MSG_DIED))
		color = COLOR_DIED;
	timestamp = get_timestamp() - philo->data->start_time;
	sem_wait(philo->data->write_sem);
	if (!simulation_ended())
		printf("%s%ld ms | Philosopher %d %s\033[0m\n", color, timestamp,
			philo->id, action);
	sem_post(philo->data->write_sem);
}

int	simulation_ended(void)
{
	return (0);
}
