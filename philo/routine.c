/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:08:23 by luide-ca          #+#    #+#             */
/*   Updated: 2025/06/25 17:52:31 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		pthread_mutex_lock(&philo->table->print_mutex);
		printf("%lu %d has taken a fork\n", get_time(), philo->id);
		pthread_mutex_unlock(&philo->table->print_mutex);
		pthread_mutex_lock(&philo->right_fork->mutex);
		pthread_mutex_lock(&philo->table->print_mutex);
		printf("%lu %d has taken a fork\n", get_time(), philo->id);
		pthread_mutex_unlock(&philo->table->print_mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		pthread_mutex_lock(&philo->table->print_mutex);
		printf("%lu %d has taken a fork\n", get_time(), philo->id);
		pthread_mutex_unlock(&philo->table->print_mutex);
		pthread_mutex_lock(&philo->left_fork->mutex);
		pthread_mutex_lock(&philo->table->print_mutex);
		printf("%lu %d has taken a fork\n", get_time(), philo->id);
		pthread_mutex_unlock(&philo->table->print_mutex);
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%lu %d is eating\n",  get_time(), philo->id);
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
	printf("%lu %d is sleeping\n", get_time(), philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
	usleep(philo->table->time_sleep * 1000);
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%lu %d is thinking\n", get_time(), philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
}


void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (1)
	{
		// pthread_mutex_lock(&p->table->sim_mutex);
		// if (is_alive == 0)
		// 	break ;
		// pthread_mutex_unlock(&p->table->sim_mutex);
		forks_n_eat(p);
		sleep_n_think(p);
	}
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