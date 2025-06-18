/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:08:23 by luide-ca          #+#    #+#             */
/*   Updated: 2025/06/18 17:08:51 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		pthread_mutex_lock(&philo->right_fork->mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		pthread_mutex_lock(&philo->left_fork->mutex);
	}
	usleep(philo->table->time_eat * 1000);
	philo->num_meals++;
	printf("timestamp_in_ms %d is eating\n", philo->id);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	return ;
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	eat(p);
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
		pthread_create(&philo->thread, NULL, routine, (void *)philo);
		i++;
	}
	return (0);
}