/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:13:06 by luide-ca          #+#    #+#             */
/*   Updated: 2025/07/01 21:46:05 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	struct s_sim	*sim;
}	t_philo;

typedef struct s_sim
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	long long		start_time;
	int				sim_ended;
	t_fork			*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_mutex;
	t_philo			*philos;
}	t_sim;

/* main.c */
int			main(int argc, char **argv);
int			validate_argv(char **argv);

/* init.c */
int			init_simulation(int argc, char **argv, t_sim *sim);
int			init_philo(t_sim *sim);
int			init_mutex(t_sim *sim);
int			init_all(int argc, char **argv, t_sim *sim);

/* actions.c */
void		take_forks(t_philo *philo);
void		eat_routine(t_philo *philo);
void		sleep_and_think(t_philo *philo);
void		*philo_routine(void *arg);

/* monitor.c */
void		*monitor_routine(void *arg);
int			check_death(t_sim *sim, int i);
int			check_meals_complete(t_sim *sim);
void		end_simulation(t_sim *sim);

/* utils.c */
long long	get_time(void);
void		precise_sleep(int ms);
void		safe_print(char *msg, t_philo *philo);
int			ft_atoi(char *str);
int			is_valid_number(char *str);

/* cleanup.c */
void		cleanup_simulation(t_sim *sim);
int			run_simulation(t_sim *sim);

#endif
