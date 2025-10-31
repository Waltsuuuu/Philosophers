#include "philosophers.h"

void	*philo_routine(void *philo_data)
{
	t_philo	*philo;

	philo = (t_philo *)philo_data;
	philo_think(philo);
	philo_take_forks(philo);
	return (NULL);
}

void	philo_think(t_philo *philo)
{
	printf("%ld %d is thinking\n",
		time_since_start_ms(philo->table->start_ms), philo->id);
}

// Take fork = Attempt to lock fork mutex.
// Even philos - left fork, then right fork.
// Odd philos - right fork, then left fork.
// fork1 = left. fork2 = right.
void	philo_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->fork1);
		printf("%ld %d has taken a fork\n",
			time_since_start_ms(philo->table->start_ms), philo->id);
		pthread_mutex_lock(philo->fork2);
		printf("%ld %d has taken a fork\n",
			time_since_start_ms(philo->table->start_ms), philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->fork2);
		printf("%ld %d has taken a fork\n",
			time_since_start_ms(philo->table->start_ms), philo->id);
		pthread_mutex_lock(philo->fork1);
		printf("%ld %d has taken a fork\n",
			time_since_start_ms(philo->table->start_ms), philo->id);
	}
}