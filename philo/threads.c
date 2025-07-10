/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:47:57 by luide-ca          #+#    #+#             */
/*   Updated: 2025/07/10 14:12:37 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_simulation(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philos)
	{
		pthread_mutex_destroy(&sim->forks[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&sim->write_mutex);
	pthread_mutex_destroy(&sim->death_mutex);
	pthread_mutex_destroy(&sim->meal_mutex);
	free(sim->forks);
	free(sim->philos);
	free(sim);
}

static int	start_thread(t_sim *sim)
{
	int		i;
	t_philo	*solo_philo;

	i = 0;
	if (sim->meals_required == 0)
		return (1);
	else if (sim->num_philos == 1)
	{
		solo_philo = &sim->philos[0];
		if (pthread_create(&solo_philo->thread, NULL,
				one_philo, solo_philo) != 0)
			return (1);
	}
	else
	{
		while (i < sim->num_philos)
		{
			if (pthread_create(&sim->philos[i].thread, NULL,
					philo_routine, (void *)&sim->philos[i]) != 0)
				return (1);
			i++;
		}
	}
	return (0);
}

static int	create_threads(t_sim *sim, pthread_t *monitor)
{
	int	i;

	sim->start_time = get_time();
	i = 0;
	while (i < sim->num_philos)
	{
		sim->philos[i].last_meal_time = sim->start_time;
		i++;
	}
	if (pthread_create(monitor, NULL, monitor_routine, (void *)sim) != 0)
		return (1);
	i = 0;
	if (start_thread(sim) != 0)
		return (1);
	return (0);
}

static void	join_threads(t_sim *sim, pthread_t monitor)
{
	int	i;

	pthread_join(monitor, NULL);
	i = 0;
	while (i < sim->num_philos)
	{
		pthread_join(sim->philos[i].thread, NULL);
		i++;
	}
}

int	run_simulation(t_sim *sim)
{
	pthread_t	monitor;

	if (create_threads(sim, &monitor) != 0)
		return (1);
	join_threads(sim, monitor);
	return (0);
}
