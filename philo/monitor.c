/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:51:49 by luide-ca          #+#    #+#             */
/*   Updated: 2025/07/04 16:39:02 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_sim *sim, int i)
{
	long long	current_time;
	long long	last_meal_time;

	pthread_mutex_lock(&sim->meal_mutex);
	last_meal_time = sim->philos[i].last_meal_time;
	pthread_mutex_unlock(&sim->meal_mutex);
	current_time = get_time();
	if (current_time - last_meal_time > sim->time_to_die)
	{
		end_simulation(sim);
		pthread_mutex_lock(&sim->write_mutex);
		printf("%lld %d died\n", current_time - sim->start_time,
			sim->philos[i].id);
		pthread_mutex_unlock(&sim->write_mutex);
		return (1);
	}
	return (0);
}

int	check_meals_complete(t_sim *sim)
{
	int	i;
	int	all_ate_enough;

	if (sim->meals_required == -1)
		return (0);
	all_ate_enough = 1;
	i = 0;
	while (i < sim->num_philos)
	{
		pthread_mutex_lock(&sim->meal_mutex);
		if (sim->philos[i].meals_eaten < sim->meals_required)
		{
			all_ate_enough = 0;
			pthread_mutex_unlock(&sim->meal_mutex);
			break ;
		}
		pthread_mutex_unlock(&sim->meal_mutex);
		i++;
	}
	if (all_ate_enough)
	{
		end_simulation(sim);
		return (1);
	}
	return (0);
}

void	end_simulation(t_sim *sim)
{
	pthread_mutex_lock(&sim->death_mutex);
	sim->sim_ended = 1;
	pthread_mutex_unlock(&sim->death_mutex);
}

void	*monitor_routine(void *arg)
{
	t_sim	*sim;
	int		i;

	sim = (t_sim *)arg;
	while (1)
	{
		i = 0;
		while (i < sim->num_philos)
		{
			if (check_death(sim, i))
				return (NULL);
			i++;
		}
		if (check_meals_complete(sim))
			return (NULL);
		usleep(1000);
	}
}
