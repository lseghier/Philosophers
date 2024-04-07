/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseghier <lseghier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:31:33 by lseghier          #+#    #+#             */
/*   Updated: 2024/04/07 02:58:12 by lseghier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (5 == ac || 6 == ac)
	{
		parse_input(&table, av);
		data_init(&table);
		dinner_start(&table);
		free_all(&table);
	}
	else
	{
		error_exit("Wrong input:\n" G \
		"Correct is ./philo 5 800 200 200 [5]" RST);
	}
}
