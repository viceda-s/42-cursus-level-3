/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 05:34:09 by viceda-s          #+#    #+#             */
/*   Updated: 2025/07/27 16:25:48 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_table	table;
	int		i;

	if (parse_arguments(argc, argv, &table.data) == -1)
		return (1);
	if (validate_arguments(&table.data) == -1)
		return (1);
	if (init_table(&table) == -1)
		return (1);
	start_simulation(&table);
	i = 0;
	while (i < table.data.nb_philo)
		pthread_join(table.philos[i++].thread, NULL);
	pthread_join(table.monitor, NULL);
	cleanup_table(&table);
	return (0);
}
