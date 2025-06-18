/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:13:02 by luide-ca          #+#    #+#             */
/*   Updated: 2025/06/18 12:15:34 by luide-ca         ###   ########.fr       */
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
	while (++i <= table->num_forks)
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

void	*eat(void* arg)
{
	static int	meal_num;

	meal_num = 0;
	pthread_mutex_lock(&fork1);
	pthread_mutex_lock(&fork2);
	meal_num++;
    printf("eating... %d philo: %s\n", meal_num, (char *)arg);
    pthread_mutex_unlock(&fork1);
	pthread_mutex_unlock(&fork2);
	return (0);
}

int	main(void)
{
	// all philos as threads
	pthread_t philo1;
	pthread_t philo2;
	pthread_t philo3;
	pthread_t philo4;

	// Initialize the mutex
	pthread_mutex_init(&fork1, NULL);
	pthread_mutex_init(&fork2, NULL);
	pthread_mutex_init(&fork3, NULL);
	pthread_mutex_init(&fork4, NULL);

	// creating threads
	pthread_create(&philo1, NULL, eat, "philo1");
	pthread_create(&philo2, NULL, eat, "philo2");
	pthread_create(&philo3, NULL, eat, "philo3");
	pthread_create(&philo4, NULL, eat, "philo4");

	// join the threads
	pthread_join(philo1, NULL);
	pthread_join(philo2, NULL);
	pthread_join(philo3, NULL);
	pthread_join(philo4, NULL);

	// Destroy the mutex
	pthread_mutex_destroy(&fork1);
	pthread_mutex_destroy(&fork2);
	pthread_mutex_destroy(&fork3);
	pthread_mutex_destroy(&fork4);

	return (0);
}
