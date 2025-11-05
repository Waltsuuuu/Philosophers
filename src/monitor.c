#include "philosophers.h"

void	run_monitor(t_table *table)
{
	int		i;
	long	now;

	while (get_end_sim(table) == FALSE)
	{
		i = 0;
		while (i < table->n_philos && get_end_sim(table) == FALSE)
		{
			now = fetch_time_ms();
			if (now - get_last_meal(&table->philos[i]) >= table->t_die)
			{
				set_end_sim(table, TRUE);
				pthread_mutex_lock(&table->print_mutex);
				printf("%ld %d died\n", time_since_start_ms(table->start_ms),
					table->philos[i].id);
				pthread_mutex_unlock(&table->print_mutex);
			}
			i++;
		}
		if (get_end_sim(table) == FALSE && all_philos_fed(table) == TRUE)
			set_end_sim(table, TRUE);
		usleep(1000);
	}
}

int	all_philos_fed(t_table *table)
{
	int	i;

	if (table->n_meals == INT_MAX)
		return (FALSE);
	i = 0;
	while (i < table->n_philos)
	{
		if (get_meals_eaten(&table->philos[i])< table->n_meals)
			return (FALSE);
		i++;
	}
	return (TRUE);
}