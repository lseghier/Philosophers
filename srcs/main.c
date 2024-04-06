#include "../includes/philo.h"

int main (int ac, char **av)
{
	t_table table;

	if (ac == 5 || ac == 6)
	{
		//correct input
		parse_input(&table, av); //OK

		init_data(&table); //OK

		dinner_start(&table);

		//creer autant de thread que de philos
		//pthread_create()
		//creer un observateur
		//join wait thread

		free_all(&table);
	}
	else
	{
		error_exit("Wrong input:\n"
		G"Correct is ./philo 5 800 200 200 [5]"RST);
	}
}
