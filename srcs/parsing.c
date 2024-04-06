#include "../includes/philo.h"

static inline bool is_digit (char c)
{
	return (c >= 48 && c <= 57);
}

static inline bool is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}


static const char *valid_input(const char *str)
{
	int len;
	int i;
	const char *number;

	i = 0;
	len = 0;

	while (is_space(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		error_exit("Only positive values !");
	if (!is_digit(str[i]))
		error_exit("Only numbers you dumb !");
	number = str;
	if (len > 10)
		error_exit("The number is too big, INT_MAX is the limit.");
	return (number);
}

static long ft_atol (const char *str)
{
	long num;

	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
		num = (num * 10) + *str++ - 48;
	if (num > INT_MAX)
		error_exit("The number is too big, INT_MAX is the limit.");
	return (num);
}


void parse_input (t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 10e3;
	table->time_to_eat = ft_atol(av[3]) * 10e3;
	table->time_to_sleep = ft_atol(av[4]) * 10e3;
	if (table->time_to_die < 6e4
	|| table->time_to_eat < 6e4
	|| table->time_to_sleep < 6e4)
	error_exit("Use timestamps major than 60ms");
	if (av[5])
		table->nbr_limit_meals = ft_atol(av[5]);
	else
		table->nbr_limit_meals = -1;
}
