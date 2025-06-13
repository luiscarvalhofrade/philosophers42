/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:13:02 by luide-ca          #+#    #+#             */
/*   Updated: 2025/06/12 21:10:20 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	moonitor()
{

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
