#include "philosophers.h"

int	exit_error(char *msg, t_table *table)
{
	printf("%s\n", msg);
	if (table)
		destroy_forks(table);
	exit(1);
}

int	destroy_forks(t_table *table)
{
	int	i;

	if (!table->forks)
		return (0);
	i = 0;
	while (i < table->n_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
	table->forks = NULL;
	return (0);
}