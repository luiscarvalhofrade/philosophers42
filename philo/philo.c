/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:13:02 by luide-ca          #+#    #+#             */
/*   Updated: 2025/06/26 14:47:52 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_mutex(t_table *table)
{
	int		i;
	t_fork	*fork;
	t_philo	*philo;

	i = 0;
	while (i < table->num_philos)
	{
		fork = &table->forks[i];
		pthread_mutex_destroy(&fork->mutex);
		philo = &table->philos[i];
		pthread_mutex_destroy(&philo->meal_mutex);
		i++;
	}
	
	return (0);
}

int	join_threads(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < table->num_philos)
	{
		philo = &table->philos[i];
		pthread_join(philo->thread, NULL);
		i++;
	}
	return (0);
}

int	validate_argv(char **argv)
{
	if (atoi(argv[1]) == 0)
		return (1);
	if (atoi(argv[2]) == 0)
		return (1);
	if (atoi(argv[3]) == 0)
		return (1);
	if (atoi(argv[4]) == 0)
		return (1);
	// if (atoi(argv[5]) == 0)
	// 	return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t monitor_thread;
	t_table	*table;
	
	if (argc < 5 || argc > 6)
		return (1);
	if (validate_argv(argv) != 0)
		return (1);
	table = malloc(sizeof(t_table));
	if (!table)
    	return (1);
	if (init_table(argv, table) != 0)
		return (1);
	pthread_mutex_init(&table->sim_mutex, NULL);
	if (run_simulation(table) != 0)
		return (1);
	pthread_create(&monitor_thread, NULL, (void *)monitor, (void *)table);
	if (join_threads(table) != 0)
		return (1);
	pthread_join(monitor_thread, NULL);
	if (destroy_mutex(table) != 0)
		return (1);
	pthread_mutex_destroy(&table->sim_mutex);
	return (0);
}
