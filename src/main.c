#include "philosophers.h"

// ARGV 
// 		ex. w/o meals	./philo 5 800 200 200 
//		ex. w/ meal 	./philo 5 800 200 200 8
// 1 n_philos
// 2 t_die
// 3 t_eat
// 4 t_sleep
// 5 [opt] n_meals

int main(int argc, char *argv[])
{
	int	args[5];

	parse_input(argc, argv, args);
	return (0);
}

// Validates input.
// Converts valid args to their integer representations.
// Stores the values in args[] array.
// Invalid input == Error and exit.
int	parse_input(int argc, char *argv[], int args[5])
{
	if ((argc != 5) && (argc != 6))
		exit_error("Usage ./philo [t_philos] [t_die] [t_eat] [t_sleep] (opt)[n_meals]");
	args[0] = pos_atoi(argv[1]);
	args[1] = pos_atoi(argv[2]);
	args[2] = pos_atoi(argv[3]);
	args[3] = pos_atoi(argv[4]);
	if (argc == 6)
		args[4] = pos_atoi(argv[5]);
	else
		args[4] = INT_MAX;
	return (0);
}

// Converts a numeric string to an integer.
// Error and exit if input is:
//  - non-numeric.
//	- negative.
//	- greater than INT_MAX.
//	- empty or 0.
int	pos_atoi(const char *s)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == ' ')
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			exit_error("ERROR: Negative values are invalid.");
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i] - '0');
		if (res > INT_MAX)
			exit_error("ERROR: Input too large.");
		i++;
	}
	if (s[i] != '\0' || res <= 0)
		exit_error("ERROR: Non-numeric or empty input.");
	return ((int)res);
}
