/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:28:56 by luide-ca          #+#    #+#             */
/*   Updated: 2025/07/01 21:48:09 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_sleep(int ms)
{
	long long	start;

	start = get_time();
	while (get_time() - start < ms)
		usleep(100);
}

void	safe_print(char *msg, t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->sim->death_mutex);
	if (philo->sim->sim_ended)
	{
		pthread_mutex_unlock(&philo->sim->death_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->sim->death_mutex);
	time = get_time() - philo->sim->start_time;
	pthread_mutex_lock(&philo->sim->write_mutex);
	printf("%lld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->sim->write_mutex);
}

int	ft_atoi(char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
