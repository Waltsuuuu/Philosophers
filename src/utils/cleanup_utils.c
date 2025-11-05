#include "philosophers.h"

/* Waits for all philo threads to terminate.
Note:
	- If a thread has already terminated, then
	  pthread_join() returns immediately.
 	- Meaning the order in which they terminate does not matter. */
int	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	return (SUCCESS);
}

int	destroy_meal_mutexes(t_table *table)
{
	int	i;

	if (!table->philos)
		return (SUCCESS);
	i = 0;
	while (i < table->meal_mutex_inited)
	{
		pthread_mutex_destroy(&table->philos[i].meal_mutex);
		i++;
	}
	return (SUCCESS);
}

int	destroy_forks(t_table *table)
{
	int	i;

	if (!table->forks)
		return (SUCCESS);
	i = 0;
	while (i < table->n_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
	table->forks = NULL;
	return (SUCCESS);
}

int	free_philos(t_table *table)
{
	if (!table->philos)
		return (0);
	free(table->philos);
	table->philos = NULL;
	return (SUCCESS);
}
