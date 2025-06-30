/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:08:23 by luide-ca          #+#    #+#             */
/*   Updated: 2025/06/30 17:14:53 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	forks(t_philo *philo)
{
	unsigned long time;

	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		pthread_mutex_lock(&philo->table->print_mutex);
		time = ft_time() - philo->table->start_simulation;
		printf("%lu %d has taken a fork\n", time, philo->id);
		pthread_mutex_unlock(&philo->table->print_mutex);
		pthread_mutex_lock(&philo->right_fork->mutex);
		pthread_mutex_lock(&philo->table->print_mutex);
		time = ft_time() - philo->table->start_simulation;
		printf("%lu %d has taken a fork\n", time, philo->id);
		pthread_mutex_unlock(&philo->table->print_mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		pthread_mutex_lock(&philo->table->print_mutex);
		time = ft_time() - philo->table->start_simulation;
		printf("%lu %d has taken a fork\n", time, philo->id);
		pthread_mutex_unlock(&philo->table->print_mutex);
		pthread_mutex_lock(&philo->left_fork->mutex);
		pthread_mutex_lock(&philo->table->print_mutex);
		time = ft_time() - philo->table->start_simulation;
		printf("%lu %d has taken a fork\n", time, philo->id);
		pthread_mutex_unlock(&philo->table->print_mutex);
	}
}

void	eat(t_philo *philo)
{
	unsigned long time;

	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = ft_time();
	pthread_mutex_lock(&philo->table->print_mutex);
	time = philo->last_meal - philo->table->start_simulation;
	printf("%lu %d is eating\n", time, philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
	usleep(philo->table->time_eat * 1000);
	philo->num_meals++;
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

void	forks_n_eat(t_philo *philo)
{
	forks(philo);
	eat(philo);
}

void	sleep_n_think(t_philo *philo)
{
	unsigned long	time;

	pthread_mutex_lock(&philo->table->print_mutex);
	time = ft_time() - philo->table->start_simulation;
	printf("%lu %d is sleeping\n", time, philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
	usleep(philo->table->time_sleep * 1000);
	pthread_mutex_lock(&philo->table->print_mutex);
	time = ft_time() - philo->table->start_simulation;
	printf("%lu %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
}


void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&p->table->sim_mutex);
		if (p->table->sim_end == 1)
		{
			pthread_mutex_unlock(&p->table->sim_mutex);
			break ;
		}
		pthread_mutex_unlock(&p->table->sim_mutex);
		forks_n_eat(p);
		sleep_n_think(p);
	}
	return (0);
}

int	run_simulation(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	table->start_simulation = ft_time();
	while (i < table->num_philos)
	{
		philo = &table->philos[i];
		philo->last_meal = ft_time();
		if (pthread_create(&philo->thread, NULL, routine, (void *)philo) != 0)
			break ;
		i++;
	}
	return (0);
}