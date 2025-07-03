/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:08:23 by luide-ca          #+#    #+#             */
/*   Updated: 2025/07/03 17:42:37 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		safe_print("has taken a fork", philo);
		pthread_mutex_lock(&philo->right_fork->mutex);
		safe_print("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		safe_print("has taken a fork", philo);
		pthread_mutex_lock(&philo->left_fork->mutex);
		safe_print("has taken a fork", philo);
	}
}

void	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->meal_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->sim->meal_mutex);
	safe_print("is eating", philo);
	precise_time(philo->sim->time_to_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

void	sleep_and_think(t_philo *philo)
{
	safe_print("is sleeping", philo);
	precise_time(philo->sim->time_to_sleep);
	safe_print("is thinking", philo);
}

void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->left_fork->mutex);
	safe_print("has taken a fork", philo);
	precise_time(philo->sim->time_to_die);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->sim->death_mutex);
		if (philo->sim->sim_ended == 1)
		{
			pthread_mutex_unlock(&philo->sim->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->sim->death_mutex);
		take_forks(philo);
		eat_routine(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}
