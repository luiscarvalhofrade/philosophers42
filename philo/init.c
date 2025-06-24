/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:07:49 by luide-ca          #+#    #+#             */
/*   Updated: 2025/06/24 17:36:28 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_table *table)
{
	int				i;
	t_philo			*philo;
	pthread_mutex_t	meal_mutex;

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
	int	i;
	pthread_mutex_t	mutex;

	i = 0;
	table->sim_mutex = mutex;
	table->num_philos = atoi(argv[1]);
	table->start_simulation = get_time();
	table->time_die = atoi(argv[2]);
	table->time_eat = atoi(argv[3]);
	table->time_sleep = atoi(argv[4]);
	table->forks = (t_fork *)malloc(sizeof(t_fork) * table->num_philos);
	if (!table->forks)
		return (1);
	while (i < table->num_philos)
	{
		pthread_mutex_init(&table->forks[i].mutex, NULL);
		table->forks[i].id = i;
		i++;
	}
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
		return (1);
	init_philos(table);
	return (0);
}