/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:51:49 by luide-ca          #+#    #+#             */
/*   Updated: 2025/06/30 17:47:19 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
    int i;
	t_table	*table;
	unsigned long current_time;
	unsigned long last_meal_time;
    
	table = (t_table *)arg;
    while (1)
    {
        i = 0;
        while (i < table->num_philos)
        {
            pthread_mutex_lock(&table->philos[i].meal_mutex);
            last_meal_time = table->philos[i].last_meal;
            pthread_mutex_unlock(&table->philos[i].meal_mutex);
            current_time = ft_time();
            if (table->time_die < (current_time - last_meal_time))
            {
                pthread_mutex_lock(&table->sim_mutex);
                table->sim_end = 1;
                pthread_mutex_unlock(&table->sim_mutex);
                printf("%lu %d died\n", current_time - table->start_simulation, table->philos[i].id);
				free_and_exit(table);
                exit (0);
            }
            usleep(1000);
            i++;
        }
    }
}
