/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:07:49 by luide-ca          #+#    #+#             */
/*   Updated: 2025/07/01 21:55:01 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_simulation(int argc, char **argv, t_sim *sim)
{
	sim->num_philos = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		sim->meals_required = ft_atoi(argv[5]);
	else
		sim->meals_required = -1;
	sim->sim_ended = 0;
	sim->forks = malloc(sizeof(t_fork) * sim->num_philos);
	if (!sim->forks)
		return (1);
	sim->philos = malloc(sizeof(t_philo) * sim->num_philos);
	if (!sim->philos)
	{
		free(sim->forks);
		return (1);
	}
	return (0);
}

int	init_philo(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philos)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].meals_eaten = 0;
		sim->philos[i].left_fork = &sim->forks[i];
		sim->philos[i].right_fork = &sim->forks[(i + 1) % sim->num_philos];
		sim->philos[i].sim = sim;
		i++;
	}
	return (0);
}

int	init_mutex(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philos)
	{
		if (pthread_mutex_init(&sim->forks[i].mutex, NULL) != 0)
			return (1);
		sim->forks[i].id = i;
		i++;
	}
	if (pthread_mutex_init(&sim->write_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&sim->death_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&sim->meal_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	init_all(int argc, char **argv, t_sim *sim)
{
	if (init_simulation(argc, argv, sim) != 0)
		return (1);
	if (init_philo(sim) != 0)
		return (1);
	if (init_mutex(sim) != 0)
		return (1);
	return (0);
}
