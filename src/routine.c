#include "philosophers.h"

void	*philo_routine(void *philo_data)
{
	t_philo	*philo;

	philo = (t_philo *)philo_data;
	sync_start(philo);
	if (philo->table->n_philos == 1)
	{
		single_philo_case(philo);
		return (NULL);
	}
	while (get_end_sim(philo->table) == FALSE
		&& philo->meals_eaten < philo->table->n_meals)
	{
		if (philo->id % 2 == 0)
		    usleep((philo->table->t_eat / 2) * 1000);

		think(philo);
		take_forks(philo);
		eat(philo);
		drop_forks(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

// All philos wait until start_ms is reached, before beginning the routine.
void	sync_start(t_philo *philo)
{
	while (fetch_time_ms() < philo->table->start_ms)
		usleep(100);
}

// 1 philo == 1 fork at table == cant eat == die.
void	single_philo_case(t_philo *philo)
{
	pthread_mutex_lock(philo->fork1);
	printf("%ld %d has taken a fork\n",
		time_since_start_ms(philo->table->start_ms), philo->id);
	usleep(philo->table->t_die * 1000);
	pthread_mutex_unlock(philo->fork1);
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

// Sets last_meal to current timestamp when philo begins eating.
// Eats (usleep) for t_eat milliseconds.
// Increases meals_eaten by one.
void	eat(t_philo *philo)
{
	printf("%ld %d is eating\n",
		time_since_start_ms(philo->table->start_ms), philo->id);
	philo->last_meal = fetch_time_ms();
	usleep(philo->table->t_eat * 1000);
	philo->meals_eaten += 1;
}

// Release 'fork mutex.
void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
}

// Sleeps (usleep) for t_sleep milliseconds.
void	philo_sleep(t_philo *philo)
{
	printf("%ld %d is sleeping\n",
		time_since_start_ms(philo->table->start_ms), philo->id);
	usleep(philo->table->t_sleep * 1000);
}