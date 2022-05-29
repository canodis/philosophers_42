/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtosun <rtosun@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:19:23 by rtosun            #+#    #+#             */
/*   Updated: 2022/05/29 12:22:11 by rtosun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	end_sim(t_simulation *sim, t_philosopher *phil)
{
	int	i;

	i = -1;
	while (++i < sim->philo_count)
		pthread_join(phil[i].thread_id, NULL);
	i = -1;
	while (++i < sim->philo_count)
		pthread_mutex_destroy(&sim->forks[i]);
	free (sim->forks);
	free (sim->philosophers);
	pthread_mutex_destroy(&sim->typing);
}

void	are_you_dead(t_simulation *sim, t_philosopher *p)
{
	int	i;

	while (!sim->all_eated)
	{
		i = -1;
		while (++i < sim->philo_count && !sim->died)
		{
			if (get_time() - p[i].last_eat > sim->die_time)
			{
				action_printer(sim, p[i].id, "oldu !");
				if (sim->philo_count == 1)
					exit(0);
				sim->died = true;
			}
			usleep(100);
			if (sim->nb_eat != -1 && p[0].eat_count >= sim->nb_eat)
				sim->all_eated = true;
		}
		if (sim->died)
			break ;
	}
}

void	eat_bro(t_philosopher *phil)
{
	t_simulation	*s;

	s = phil->sim;
	pthread_mutex_lock(&s->forks[phil->left_fork_id]);
	action_printer(s, phil->id, "catali aldi");
	pthread_mutex_lock(&s->forks[phil->right_fork_id]);
	action_printer(s, phil->id, "catali aldi");
	action_printer(s, phil->id, "yemek yiyo");
	phil->last_eat = get_time();
	phil->eat_count++;
	i_need_sleep(s->eat_time, s);
	pthread_mutex_unlock(&s->forks[phil->left_fork_id]);
	pthread_mutex_unlock(&s->forks[phil->right_fork_id]);
}

void	*thread(void *void_philo)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)void_philo;
	if (philo->id % 2 != 0)
		usleep(1000);
	while (!philo->sim->died)
	{
		eat_bro(philo);
		if (philo->sim->all_eated)
			break ;
		action_printer(philo->sim, philo->id, "uyuyor");
		i_need_sleep(philo->sim->sleep_time, philo->sim);
		action_printer(philo->sim, philo->id, "dusunuyor...");
	}
	return (NULL);
}

void	sim_start(t_simulation *sim)
{
	int				i;
	t_philosopher	*phil;

	phil = sim->philosophers;
	sim->start_time = get_time();
	i = 0;
	while (i < sim->philo_count)
	{
		pthread_create(&phil[i].thread_id, NULL, thread, &phil[i]);
		i++;
	}
	are_you_dead(sim, phil);
	end_sim(sim, phil);
	i = 0;
}
