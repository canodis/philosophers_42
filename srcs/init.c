/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtosun <rtosun@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:19:02 by rtosun            #+#    #+#             */
/*   Updated: 2022/05/29 02:30:37 by rtosun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	init_mutex(t_simulation *sim)
{
	int	i;

	i = sim->philo_count;
	while (--i >= 0)
		if (pthread_mutex_init(&sim->forks[i], NULL))
			return (false);
	if (pthread_mutex_init(&sim->typing, NULL))
		return (false);
	return (true);
}

void	init_philosophers(t_simulation *sim)
{
	int	i;

	i = sim->philo_count;
	while (--i >= 0)
	{
		sim->philosophers[i].id = i;
		sim->philosophers[i].left_fork_id = i;
		sim->philosophers[i].right_fork_id = (i + 1) % sim->philo_count;
		sim->philosophers[i].sim = sim;
		sim->philosophers[i].last_eat = get_time();
		sim->philosophers[i].eat_count = 0;
	}
}

void	init_all(t_simulation *sim, char **argv)
{
	sim->philo_count = atoi(argv[1]);
	sim->die_time = atoi(argv[2]);
	sim->eat_time = atoi(argv[3]);
	sim->sleep_time = atoi(argv[4]);
	sim->all_eated = false;
	sim->died = false;
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->philo_count);
	sim->philosophers = malloc(sizeof(t_philosopher) * sim->philo_count);
	if (argv[5])
		sim->nb_eat = atoi(argv[5]);
	else
		sim->nb_eat = -1;
	if (sim->philo_count <= 0 || sim->die_time <= 0
		||sim->eat_time <= 0 || sim->sleep_time <= 0)
	{
		printf("yanlis arguman girisi !");
		exit(0);
	}
	if (!init_mutex(sim))
		print_error("mutex init error !");
	init_philosophers(sim);
}
// option shift f