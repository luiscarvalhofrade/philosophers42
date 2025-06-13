/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:13:06 by luide-ca          #+#    #+#             */
/*   Updated: 2025/06/12 20:58:43 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_PH

# include <pthread.h>
# include <stdio.h>

typedef struct  s_infos
{
    int         num_philos;
    int         num_forks;
    int         time_eat;
    int         time_sleep;
    int         time_think;
    pthread_t   thread;
}               t_infos;

typedef struct  s_philo
{
    int right_fork;
    int left_fork;
    int philo_num;
}               t_philo;

#endif