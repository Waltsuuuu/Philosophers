#include "philosophers.h"

int	exit_error(char *msg, t_table *table)
{
	printf("%s\n", msg);
	if (table)
	{
		destroy_meal_mutexes(table);
		free_philos(table);
		destroy_forks(table);
		pthread_mutex_destroy(&table->stop_mutex);
		pthread_mutex_destroy(&table->print_mutex);
	}
	exit(FAILURE);
}

void	cleanup_allocs_and_mutexes(t_table *table)
{
	join_threads(table);
	destroy_meal_mutexes(table);
	free_philos(table);
	destroy_forks(table);
	pthread_mutex_destroy(&table->stop_mutex);
	pthread_mutex_destroy(&table->print_mutex);
}
