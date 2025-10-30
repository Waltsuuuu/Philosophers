#include "philosophers.h"

// ARGV[] 
// 		ex. w/o meals	./philo 5 800 200 200 
//		ex. w/ meal 	./philo 5 800 200 200 8
// [1] n_philos
// [2] t_die
// [3] t_eat
// [4] t_sleep
// [5] n_meals [optional] 

int main(int argc, char *argv[])
{
	t_table table;

	parse_input(argc, argv, &table);
	create_forks(&table);
	return (0);
}

// Validates and stores command line input.
// If valid: 
// 	- Converts the arguemnts their integer representations.
// 	- Stores the converted values their respective fields
// 	  inside the t_table struct.
// If invalid:
//	- Error and exit.
int	parse_input(int argc, char *argv[], t_table *table)
{
	if ((argc != 5) && (argc != 6))
		exit_error("Usage ./philo [t_philos] [t_die] [t_eat] [t_sleep] (opt)[n_meals]");
	table->n_philos = pos_atoi(argv[1]);
	table->t_die = pos_atoi(argv[2]);
	table->t_eat = pos_atoi(argv[3]);
	table->t_sleep = pos_atoi(argv[4]);
	if (argc == 6)
		table->n_meals = pos_atoi(argv[5]);
	else
		table->n_meals = INT_MAX;
	return (0);
}

// Allocates memory for all fork mutexes and initialies each mutex.
// On malloc() or mutex_init() failure, cleanup and exit.
int	create_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philos);
	if (!table->forks)
		return(exit_error("ERROR: malloc failure."));
	i = 0;
	while (i < table->n_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->forks[i]);
			free(table->forks);
			table->forks = NULL;
			return (exit_error("ERROR: mutex init failure"));
		}
		i++;
	}
	return (0);
}
