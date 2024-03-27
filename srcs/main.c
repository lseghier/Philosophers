#include "philo.h"

int main (int ac, char **av)
{
	t_table table;

	if (ac < 5 || ac > 6)
	{
		//correct input
		parse_input(&table, av); //OK

		data_init(&table);

		dinner_start(&table);

		free_all(&table);
	}
	else
	{
		error_exit("Wrong input:\n"
		G"Correct is ./philo 5 800 200 200 [5]"RST);
	}
}
