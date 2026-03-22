/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/03/22 16:00:00 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	init_semaphores(t_table *table)
{
	sem_unlink("philo_forks");
	sem_unlink("philo_write");
	sem_unlink("philo_death");
	table->data.forks = sem_open("philo_forks", O_CREAT | O_EXCL,
			0644, table->data.nb_philo);
	if (table->data.forks == SEM_FAILED)
		return (0);
	table->data.write_sem = sem_open("philo_write", O_CREAT | O_EXCL,
			0644, 1);
	if (table->data.write_sem == SEM_FAILED)
		return (0);
	table->data.death_sem = sem_open("philo_death", O_CREAT | O_EXCL,
			0644, 1);
	if (table->data.death_sem == SEM_FAILED)
		return (0);
	return (1);
}

void	destroy_semaphores(t_table *table)
{
	sem_close(table->data.forks);
	sem_close(table->data.write_sem);
	sem_close(table->data.death_sem);
	sem_unlink("philo_forks");
	sem_unlink("philo_write");
	sem_unlink("philo_death");
}
