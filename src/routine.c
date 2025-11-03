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
		&& get_meals_eaten(philo) < philo->table->n_meals)
	{
		if ((philo->id % 2) == 0)
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
	safe_print(philo, "has taken a fork");
	usleep(philo->table->t_die * 1000);
	pthread_mutex_unlock(philo->fork1);
}


void	think(t_philo *philo)
{
	safe_print(philo, "is thinking");
}

// Take fork == Attempt to lock 'fork' mutex.
// Once mutex locked - Prints "[timestamp] [philo_id] has taken a fork".
void	take_forks(t_philo *philo)
{

	pthread_mutex_lock(philo->fork1);
	safe_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->fork2);
	safe_print(philo, "has taken a fork");
}

// Sets last_meal to current timestamp when philo begins eating.
// Eats (usleep) for t_eat milliseconds.
// Increases meals_eaten by one.
void	eat(t_philo *philo)
{
	safe_print(philo, "is eating");
	set_last_meal(philo, fetch_time_ms());
	increment_meals_eaten(philo);
	usleep(philo->table->t_eat * 1000);
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
	safe_print(philo, "is sleeping");
	usleep(philo->table->t_sleep * 1000);
}