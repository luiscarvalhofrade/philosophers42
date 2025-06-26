/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:51:49 by luide-ca          #+#    #+#             */
/*   Updated: 2025/06/26 14:48:29 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitor(t_table *table)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < table->num_philos)
		{
			if (table->time_die < (ft_time() - ((t_philo *)&table->philos[i])->last_meal))
			{
				pthread_mutex_lock(&table->sim_mutex);
				table->sim_end = 1;
				pthread_mutex_unlock(&table->sim_mutex);
				printf("%lu %d died\n", ft_time() - table->start_simulation, ((t_philo *)&table->philos[i])->id);
				return (1);
			}
			usleep(1000);
			i++;
		}
	}
	return (0);
}
