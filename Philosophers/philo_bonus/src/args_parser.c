/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/03/22 16:00:00 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	parse_arguments(int argc, char **argv, t_data *data)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->nb_times_to_eat = -1;
	if (argc == 6)
		data->nb_times_to_eat = ft_atoi(argv[5]);
	return (validate_arguments(data));
}

int	validate_arguments(t_data *data)
{
	if (data->nb_philo < 1 || data->nb_philo > 200)
	{
		printf("Error: number_of_philosophers must be between 1 and 200\n");
		return (0);
	}
	if (data->time_to_die < 1 || data->time_to_eat < 1
		|| data->time_to_sleep < 1)
	{
		printf("Error: time values must be positive\n");
		return (0);
	}
	if (data->nb_times_to_eat == 0)
	{
		printf("Error: number_of_times must be positive\n");
		return (0);
	}
	return (1);
}
