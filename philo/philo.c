/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:13:02 by luide-ca          #+#    #+#             */
/*   Updated: 2025/06/17 21:15:43 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// all forks as mutexes
pthread_mutex_t fork1;
pthread_mutex_t fork2;
pthread_mutex_t fork3;
pthread_mutex_t fork4;

void	*eat(void* arg)
{
	static int	meal_num;

	meal_num = 0;
	pthread_mutex_lock(&fork1);
	pthread_mutex_lock(&fork2);
	meal_num++;
    printf("eating... %d philo: %s\n", meal_num, (char *)arg);
    pthread_mutex_unlock(&fork1);
	pthread_mutex_unlock(&fork2);
	return (0);
}

int	main(void)
{
	// all philos as threads
	pthread_t philo1;
	pthread_t philo2;
	pthread_t philo3;
	pthread_t philo4;

	// Initialize the mutex
	pthread_mutex_init(&fork1, NULL);
	pthread_mutex_init(&fork2, NULL);
	pthread_mutex_init(&fork3, NULL);
	pthread_mutex_init(&fork4, NULL);

	// creating threads
	pthread_create(&philo1, NULL, eat, "philo1");
	pthread_create(&philo2, NULL, eat, "philo2");
	pthread_create(&philo3, NULL, eat, "philo3");
	pthread_create(&philo4, NULL, eat, "philo4");

	// join the threads
	pthread_join(philo1, NULL);
	pthread_join(philo2, NULL);
	pthread_join(philo3, NULL);
	pthread_join(philo4, NULL);

	// Destroy the mutex
	pthread_mutex_destroy(&fork1);
	pthread_mutex_destroy(&fork2);
	pthread_mutex_destroy(&fork3);
	pthread_mutex_destroy(&fork4);

	return (0);
}
