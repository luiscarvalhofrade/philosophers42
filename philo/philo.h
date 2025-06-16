/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:13:06 by luide-ca          #+#    #+#             */
/*   Updated: 2025/06/16 16:03:18 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_PH

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>

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

typedef struct  s_fork
{
    int num_fork;
}               t_fork;

typedef struct  s_philo
{
    int start_routine;
    int right_fork;
    int left_fork;
    int philo_num;
}               t_philo;

#endif