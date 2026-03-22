/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/07/29 16:12:00 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long milliseconds)
{
	long	start;

	start = get_timestamp();
	while ((get_timestamp() - start) < milliseconds)
		usleep(500);
}

void	print_action(t_philo *philo, char *action)
{
	long	timestamp;
	char	*color;

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
	pthread_mutex_lock(&philo->data->write_mutex);
	if (!philo->data->simulation_end)
	{
		timestamp = get_timestamp() - philo->data->start_time;
		printf("%s%ld ms | Philosopher %d %s%s\n", color, timestamp,
			philo->id, action, COLOR_RESET);
	}
	pthread_mutex_unlock(&philo->data->write_mutex);
}

int	simulation_ended(t_philo *philo)
{
	int	ended;

	pthread_mutex_lock(&philo->data->death_mutex);
	ended = philo->data->simulation_end;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (ended);
}
