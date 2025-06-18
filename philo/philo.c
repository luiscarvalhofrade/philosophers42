/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:13:02 by luide-ca          #+#    #+#             */
/*   Updated: 2025/06/18 20:00:09 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_mutex(t_table *table)
{
	int		i;
	t_fork	*fork;

	i = 0;
	while (i < table->num_philos)
	{
		fork = &table->forks[i];
		pthread_mutex_destroy(&fork->mutex);
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
	t_table	*table;
	
	//validate if we have the right number of params
	if (argc < 5 || argc > 6)
		return (1);
	// validate if all params are integers
	if (validate_argv(argv) != 0)
		return (1);
	// init table
	table = malloc(sizeof(t_table));
	if (!table)
    	return (1);
	// init forks, philos
	if (init_table(argv, table) != 0)
		return (1);
	// creating threads
	pthread_mutex_init(&table->sim_mutex, NULL);
	if (run_simulation(table) != 0)
		return (1);
	// join the threads
	if (join_threads(table) != 0)
		return (1);
	// Destroy the mutex
	if (destroy_mutex(table) != 0)
		return (1);
	pthread_mutex_destroy(&table->sim_mutex);
	return (0);
}
