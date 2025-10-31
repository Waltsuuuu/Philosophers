#include "philosophers.h"

void	*philo_routine(void *philo_data)
{
	t_philo	*philo;

	philo = (t_philo *)philo_data;
	philo_think(philo);
	return (NULL);
}

void	philo_think(t_philo *philo)
{
	printf("%ld %d is thinking\n",
		time_since_start_ms(philo->table->start_ms), philo->id);
}