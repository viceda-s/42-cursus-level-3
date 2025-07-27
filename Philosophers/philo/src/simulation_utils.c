/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/07/27 16:52:25 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

char	*get_action_color(char *action)
{
	if (strncmp(action, "has taken a fork", 16) == 0)
		return (COLOR_FORK);
	else if (strncmp(action, "is eating", 9) == 0)
		return (COLOR_EAT);
	else if (strncmp(action, "is sleeping", 11) == 0)
		return (COLOR_SLEEP);
	else if (strncmp(action, "is thinking", 11) == 0)
		return (COLOR_THINK);
	else if (strncmp(action, "died", 4) == 0)
		return (COLOR_DIED);
	return (COLOR_RESET);
}

void	print_action_colored(t_philo *philo, char *action, char *color)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->write_mutex);
	if (!simulation_ended(philo))
	{
		timestamp = get_timestamp() - philo->data->start_time;
		printf("%s%ld %d %s%s\n", color, timestamp, philo->id, action,
			COLOR_RESET);
	}
	pthread_mutex_unlock(&philo->data->write_mutex);
}

void	print_action(t_philo *philo, char *action)
{
	char	*color;

	color = get_action_color(action);
	print_action_colored(philo, action, color);
}

int	simulation_ended(t_philo *philo)
{
	int	ended;

	pthread_mutex_lock(&philo->data->death_mutex);
	ended = philo->data->simulation_end;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (ended);
}

int	simulation_ended_unsafe(t_data *data)
{
	return (data->simulation_end);
}
