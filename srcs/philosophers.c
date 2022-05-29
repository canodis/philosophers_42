/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtosun <rtosun@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:17:56 by canodis           #+#    #+#             */
/*   Updated: 2022/05/12 17:16:05 by rtosun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;

	if (argc == 6 || argc == 5)
	{
		init_all(&sim, argv);
		sim_start(&sim);
	}
	else
		print_error("Eksik veya fazla arguman !");
}
