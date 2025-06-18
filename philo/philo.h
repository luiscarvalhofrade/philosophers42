/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:13:06 by luide-ca          #+#    #+#             */
/*   Updated: 2025/06/18 12:13:50 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>

typedef struct  s_fork
{
    int             id;
    pthread_mutex_t fork;
}               t_fork;

typedef struct  s_philo
{
    int     id;
    int     num_meals;
    int     last_meal;
    t_table *table;
    t_fork  *right_fork;
    t_fork  *left_fork;
}               t_philo;

typedef struct  s_table
{
    int         num_philos;
    int         num_forks;
    int         time_die;
    int         time_eat;
    int         time_sleep;
    int         num_meals;
    int         start_simulation;
    t_philo     *philos;
    t_fork      *forks;
}               t_table;

#endif