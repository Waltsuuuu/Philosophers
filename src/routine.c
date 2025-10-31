#include "philosophers.h"

void	*philo_routine(void *philo_data)
{
	t_philo	*philo;

	philo = (t_philo *)philo_data;
	think(philo);
	take_forks(philo);
	drop_forks(philo);
	return (NULL);
}

void	think(t_philo *philo)
{
	printf("%ld %d is thinking\n",
		time_since_start_ms(philo->table->start_ms), philo->id);
}

// Take fork == Attempt to lock 'fork' mutex.
// Pick up order:
// 	- Even philos - fork1 (left), then fork2 (right).
// 	- Odd philos  - fork2 (right), then fork1 (left).
void	take_forks(t_philo *philo)
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

// Release 'fork mutex.
void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
}