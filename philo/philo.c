/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:13:02 by luide-ca          #+#    #+#             */
/*   Updated: 2025/06/18 13:46:48 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->num_philos)
	{
		philo = &table->philos[i];
		philo->id = i;
		philo->num_meals = 0;
		philo->left_fork = &table->forks[i];
		philo->right_fork = &table->forks[(i + 1) % table->num_philos];
		philo->table = table;
		philo->last_meal = table->start_simulation;
		i++;
	}
	return (0);
}

int	init_table(t_table *table)
{
	int		i;

	i = -1;
	table->forks = (t_fork *)malloc(sizeof(t_fork) * table->num_philos);
	if (!table->forks)
		return (1);
	while (++i <= table->num_philos)
	{
		pthread_mutex_init(&table->forks[i].fork, NULL);
		table->forks[i].id = i;
	}
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
		return (1);
	init_philos(table);
	return (0);
}

void	*eat(t_table *table)
{
	t_philo	*philo;
	int		i;
	i = 0;

	while (i < 8)
	{
		philo = &table->philos[i];
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		philo->num_meals++;
		printf("eating... %d philo: %s\n", philo->num_meals, philo->id);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		i++;
	}
	return (0);
}

int	run_simulation(t_table *table)
{
	t_philo	philo;
	int		i;

	i = 0;
	while (i < table->num_philos)
	{
		philo = table->philos[i];
		pthread_create(&philo, NULL, eat, (t_table *)table);
		i++;
	}
	return (0);
}

int	destroy_mutex(t_table *table)
{
	int		i;
	t_fork	fork;

	i = 0;
	while (i < table->num_philos)
	{
		fork = table->forks[i];
		pthread_mutex_destroy(&fork);
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
		pthread_join(&philo->thread, NULL);
		i++;
	}
	return (0);
}

int	main(void)
{
	t_table	*table;

	// init table, forks, philos
	if (init_table(&table) != 0)
		return (1);
	// creating threads
	if (run_simulation(table) != 0)
		return (1);
	// join the threads
	if (join_threads(table) != 0)
		return (1);
	// Destroy the mutex
	if (destroy_mutex(&table) != 0)
		return (1);
	return (0);
}
