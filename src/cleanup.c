#include "philosophers.h"

int	exit_error(char *msg, t_table *table)
{
	printf("%s\n", msg);
	if (table)
	{
		free_philos(table);
		destroy_forks_and_meal_mutexes(table);
		pthread_mutex_destroy(&table->stop_mutex);
	}
	exit(FAILURE);
}

int	destroy_forks_and_meal_mutexes(t_table *table)
{
	int	i;

	if (!table->forks)
		return (SUCCESS);
	i = 0;
	while (i < table->n_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i].meal_mutex);
		i++;
	}
	free(table->forks);
	table->forks = NULL;
	return (SUCCESS);
}

int free_philos(t_table *table)
{
	if (!table->philos)
		return (0);
	free(table->philos);
	table->philos = NULL;
	return (SUCCESS);
}