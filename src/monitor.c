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
			if (now - table->philos[i].last_meal >= table->t_die)
			{
				printf("%ld %d died\n",
					time_since_start_ms(table->start_ms), table->philos[i].id);
				set_end_sim(table, TRUE);
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
		if (table->philos[i].meals_eaten < table->n_meals)
			return (FALSE);
		i++;
	}
	return (TRUE);
}