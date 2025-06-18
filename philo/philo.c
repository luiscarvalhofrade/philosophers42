/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:13:02 by luide-ca          #+#    #+#             */
/*   Updated: 2025/06/18 14:44:27 by luide-ca         ###   ########.fr       */
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

int	init_table(char **argv, t_table *table)
{
	int		i;

	i = -1;
	table->num_philos = atoi(argv[1]);
	//table->start_simulation = gettimeofday();
	table->forks = (t_fork *)malloc(sizeof(t_fork) * table->num_philos);
	if (!table->forks)
		return (1);
	while (++i <= table->num_philos)
	{
		pthread_mutex_init(&table->forks[i].mutex, NULL);
		table->forks[i].id = i;
	}
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
		return (1);
	init_philos(table);
	return (0);
}

void	*eat(void *table)
{
	t_philo	*philo;
	t_table *t;
	int		i;

	i = 0;	
	t = (t_table *)table;
	while (i < t->num_philos)
	{
		philo = &t->philos[i];
		pthread_mutex_lock(&philo->left_fork->mutex);
		pthread_mutex_lock(&philo->right_fork->mutex);
		philo->num_meals++;
		printf("eating... %d philo: %d\n", philo->num_meals, philo->id);
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
		i++;
	}
	return (0);
}

int	run_simulation(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < table->num_philos)
	{
		philo = &table->philos[i];
		pthread_create(&philo->thread, NULL, eat, (void *)table);
		i++;
	}
	return (0);
}

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
	if (atoi(argv[5]) == 0)
		return (1);
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
	// init table, forks, philos
	if (init_table(argv, table) != 0)
		return (1);
	// creating threads
	if (run_simulation(table) != 0)
		return (1);
	// join the threads
	if (join_threads(table) != 0)
		return (1);
	// Destroy the mutex
	if (destroy_mutex(table) != 0)
		return (1);
	return (0);
}
