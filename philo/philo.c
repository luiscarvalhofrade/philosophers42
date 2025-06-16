/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:13:02 by luide-ca          #+#    #+#             */
/*   Updated: 2025/06/16 18:25:46 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


/*
	first, i need to imagine how to make the dyanmic between philosophers, each one
	is the first when he gets the first and the second fork and so on. Second, how
	to deal with other philos, if anyother is set whatsoever.

	1. set each philosopher: unique number

	2. set forks: unique number

	here the nth philo gets the nth and the (n + 1)th fork, the (n + 1)th philo, gets
	tje (n + 1)th plus the (n + 2)th forks and so on.

	if we have t philos:

	#1 philo -> #1 and #2 forks
	#2 philo -> #2 and #3 forks
	.
	.
	.
	#n philo -> #n and #(n+1) forks
	.
	.
	.
	#(t-1) philo -> #(t-1) and #t forks
	#t philo -> #t and #1 forks

	#1 philo gets forks #1 and #2, all other philos start to count the time?
	#1 start to eats, all other wait 200 miliseconds
*/

int	monitor()
{

}

int	routine()
{

}

int	init(int *table_infos)
{
	t_table	*table;
	int		i;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	if (init_table(&table, table_infos) != 0)
		return (NULL);
	table->philos = malloc(sizeof(t_philo) * table_infos[0]);
	if (!table->philos)
	{
		while (i-- > 0)
		free(table->forks);
		error_exit(table, "Malloc failed (philos)\n");
	}
	if (init_philos(&table) != 0)
		return (NULL);
	return (0);
}

int	init_table(t_table *table, int *table_infos)
{
	table->num_forks = table_infos[0];
	table->num_philos = table_infos[0];
	table->time_die = table_infos[1];
	table->time_eat = table_infos[2];
	table->time_sleep = table_infos[3];
	table->start_simulation = get_time();
	if (table_infos[4] != 0)
		table->num_meals = table_infos[4];
	return (0);
}

int init_philos(t_table *table)
{
	int	i;
	t_philo	*philo;

	i = 0;
	while (table->num_philos > i)
	{
		philo = malloc(sizeof(t_philo));
		if (!philo)
			return (NULL);
	}
	return (0);
}

int	run_simulation(void)
{
	/*
		1. set the table
		while (number of times to eat || is_everyboy alive)
		{
			2. nth philo get the right and the left forks
				2.1. start to count the time for the nth philo to eat
				2.2. start to count the time to the others to not to die
				2.3. nth philo leaves the forks on the table
				2.4. time for nth philo not to die starts
		}
		3. monitor checks with anybody died, if it is true finish program
	*/
}


int	main(int argc, char **argv)
{

	if (argc < 5 || argc > 6)
		printf("Error");
	// validate if all inputs are of the right type

	// transform the argv into integers
	
	// init instances of philosophers
	init_philo();
	// run the simulation
	run_simulation();
	return (0);
}
