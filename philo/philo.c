/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:13:02 by luide-ca          #+#    #+#             */
/*   Updated: 2025/07/01 21:46:28 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_argv(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_valid_number(argv[i]) || ft_atoi(argv[i]) <= 0)
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_sim	*sim;

	if (argc < 5 || argc > 6)
		return (1);
	if (validate_argv(argv) != 0)
		return (1);
	sim = malloc(sizeof(t_sim));
	if (!sim)
		return (1);
	if (init_all(argc, argv, sim) != 0)
	{
		free(sim);
		return (1);
	}
	if (run_simulation(sim) != 0)
	{
		cleanup_simulation(sim);
		return (1);
	}
	cleanup_simulation(sim);
	return (0);
}
