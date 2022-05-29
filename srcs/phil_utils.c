/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtosun <rtosun@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:19:08 by rtosun            #+#    #+#             */
/*   Updated: 2022/05/29 02:30:53 by rtosun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_error(char *message)
{
	printf("%s%s\n", CRED, message);
	exit(0);
}

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	action_printer(t_simulation *sim, int id, char *msg)
{
	pthread_mutex_lock(&sim->typing);
	if (!sim->died)
	{
		printf("ms : %lli ", get_time() - sim->start_time);
		printf(" ps : %i %s\n", id, msg);
	}
	pthread_mutex_unlock(&sim->typing);
}

void	i_need_sleep(long long time, t_simulation *sim)
{
	long long	t;

	t = get_time();
	while (!(sim->died))
	{
		if (get_time() - t >= time)
			break ;
		usleep(32);
	}
}

int	ft_atoi(char *ptr)
{
	int	res;
	int	pn;
	int	i;

	i = 0;
	pn = 1;
	res = 0;
	while (ptr[i] == ' ' || ptr[i] >= 9 && ptr[i] <= 13)
		i++;
	while (ptr[i] == '+' || ptr[i] == '-')
	{
		if (ptr[i] == '-')
			pn *= -1;
		i++;
	}
	while (i >= '0' && i <= '9' && ptr[i])
	{
		res = (res * 10) + ptr[i] - 48;
		i++;
	}
	return (res * pn);
}
