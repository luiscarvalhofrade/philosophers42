/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:13:06 by luide-ca          #+#    #+#             */
/*   Updated: 2025/06/26 17:55:34 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct  s_fork
{
    int             id;
    pthread_mutex_t mutex;
}               t_fork;

typedef struct  s_table t_table;

typedef struct  s_philo
{
    int				id;
    int				num_meals;
    unsigned long	last_meal;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
    t_table			*table;
    t_fork 			*right_fork;
    t_fork			*left_fork;
}               t_philo;

typedef struct  s_table
{
    int         num_philos;
    unsigned long   time_die;
    unsigned long   time_eat;
    unsigned long   time_sleep;
    int         num_meals;
	unsigned long   sim_end;
    unsigned long	start_simulation;
	pthread_mutex_t print_mutex;
    pthread_mutex_t sim_mutex;
    t_philo     *philos;
    t_fork      *forks;
}               t_table;

int	init_table(char **argv, t_table *table);
int	run_simulation(t_table *table);

unsigned long	ft_time(void);
int				monitor(t_table *table);

#endif