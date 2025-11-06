#include "philosophers.h"

/*
Philo threads repeat routine while 'end_sim' is FALSE.
Routie: Think, Pick-up forks, Eat, Drop forks, Sleep.
*/
void	*philo_routine(void *philo_data)
{
	t_philo	*philo;
	long	started_sleeping;

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
		think_pause(philo);
		take_forks_and_eat(philo);
		safe_print(philo, "is sleeping");
		started_sleeping = current_time_ms();
		while (get_end_sim(philo->table) == FALSE
			&& current_time_ms() - started_sleeping < philo->table->t_sleep)
			usleep(200);
	}
	return (NULL);
}

/* 1 philo == 1 fork at table == cant eat == death */
void	single_philo_case(t_philo *philo)
{
	pthread_mutex_lock(philo->fork1);
	safe_print(philo, "has taken a fork");
	usleep(philo->table->t_die * 1000);
	pthread_mutex_unlock(philo->fork1);
}

/*
Delays the routine start of philos with odd numbered id,
to prevent large wave of simultaneous fork pick ups.
If 'n_philos' > 100;
	- Odd philos wait ~'t_eat'.
If 'n_philos' < 100:
	- Odd philos wait ~(t_eat / 2).
*/
void	stagger_start(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		if (philo->table->n_philos > 100)
		{
			while (get_end_sim(philo->table) == FALSE
				&& sim_runtime_ms(philo->table->start_ms) < philo->table->t_eat)
				usleep(500);
		}
		else
		{
			while (get_end_sim(philo->table) == FALSE
				&& sim_runtime_ms(philo->table->start_ms)
				< (philo->table->t_eat / 2))
				usleep(500);
		}
	}
}

/* Think "wait buffer" to prevent re-syncing after 'start_stagger()'.
- If even 'n_philos': t_think for maximum of 25% of (t_die - t_eat - t_sleep).
- If odd  'n_philos': t_think for maximum of 75% of (t_die - t_eat - t_sleep).
If the philos give 't_think' time is longer than the time they have until they
MUST be eating the next meal, then t_think is set to the time they have until
their next meal.
*/
void	think_pause(t_philo *philo)
{
	long	slack;
	long	max_think;
	long	time_left;
	long	t_think;
	long	started_thinking;

	slack = philo->table->t_die - philo->table->t_eat - philo->table->t_sleep;
	if (slack <= 0)
		return ;
	max_think = slack / 4;
	if (philo->table->n_philos % 2 != 0)
		max_think = slack - (slack / 4);
	time_left = philo->table->t_die
		- (current_time_ms()
			- get_last_meal(philo)) - philo->table->t_eat;
	if (time_left <= 0)
		return ;
	t_think = max_think;
	if (t_think > time_left)
		t_think = time_left;
	started_thinking = current_time_ms();
	while (get_end_sim(philo->table) == FALSE
		&& (current_time_ms() - started_thinking) < t_think)
		usleep(500);
}

/* Take fork == Attempt to lock 'fork' mutex.
Last philo picks up forks in opposite order to prevent deadlock.
Once mutex locked:
1. Prints "[timestamp] [philo_id] has taken a fork".
2. Eats for 't_eat' milliseconds,
   while checking 'end_sim' every 500 microseconds.
*/
void	take_forks_and_eat(t_philo *philo)
{
	long	started_eating;

	if (philo->id == philo->table->n_philos)
	{
		pthread_mutex_lock(philo->fork1);
		safe_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork2);
		safe_print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->fork2);
		safe_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork1);
		safe_print(philo, "has taken a fork");
	}
	set_last_meal(philo, current_time_ms());
	safe_print(philo, "is eating");
	started_eating = current_time_ms();
	while (get_end_sim(philo->table) == FALSE
		&& current_time_ms() - started_eating < philo->table->t_eat)
		usleep(500);
	pthread_mutex_unlock(philo->fork2);
	pthread_mutex_unlock(philo->fork1);
	increment_meals_eaten(philo);
}
