#include "philosophers.h"

// Routine:
// Think, Pick-up forks, Eat, Drop forks, Sleep.
void	*philo_routine(void *philo_data)
{
	t_philo	*philo;
	long	current_time;

	philo = (t_philo *)philo_data;
	wait_for_start_ms(philo);
	if (philo->table->n_philos == 1)
	{
		single_philo_case(philo);
		return (NULL);
	}
	stagger_start(philo);
	while (get_end_sim(philo->table) == FALSE
		&& get_meals_eaten(philo) < philo->table->n_meals)
	{
		safe_print(philo, "is thinking");
		take_forks_and_eat(philo);
		safe_print(philo, "is sleeping");
		current_time = fetch_time_ms();
		while (get_end_sim(philo->table) == FALSE
			&& fetch_time_ms() - current_time < philo->table->t_sleep)
			usleep(200);
	}
	return (NULL);
}

// Wait until the clock hits 'start_ms' before starting the routine.
void	wait_for_start_ms(t_philo *philo)
{
	while (fetch_time_ms() < philo->table->start_ms)
		usleep(500);
}

// Delays the routine start of philos with odd numbered id,
// to prevent large wave of simultaneous fork pick ups.
// n_philos > 100;
// 	- Odd philos wait roughly 't_eat'.
// n_philos < 100:
// 	- Odd philos wait 0.5ms.
void	stagger_start(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		if (philo->table->n_philos > 100)
		{
			while (get_end_sim(philo->table) == FALSE
				&& time_since_start_ms(philo->table->start_ms) < philo->table->t_eat)
			usleep(500);
		}
		else
			usleep(500);
	}
}

// 1 philo == 1 fork at table == cant eat == die.
void	single_philo_case(t_philo *philo)
{
	pthread_mutex_lock(philo->fork1);
	safe_print(philo, "has taken a fork");
	usleep(philo->table->t_die * 1000);
	pthread_mutex_unlock(philo->fork1);
}

// Take fork == Attempt to lock 'fork' mutex.
// Once mutex locked - Prints "[timestamp] [philo_id] has taken a fork".
void	take_forks_and_eat(t_philo *philo)
{
	long current_time;

	pthread_mutex_lock(philo->fork1);
	safe_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->fork2);
	safe_print(philo, "has taken a fork");
	set_last_meal(philo, fetch_time_ms());
	safe_print(philo, "is eating");
	current_time = fetch_time_ms();
	while (get_end_sim(philo->table) == FALSE
		&& fetch_time_ms() - current_time < philo->table->t_eat)
		usleep(500);
	pthread_mutex_unlock(philo->fork2);
	pthread_mutex_unlock(philo->fork1);
	increment_meals_eaten(philo);
}
