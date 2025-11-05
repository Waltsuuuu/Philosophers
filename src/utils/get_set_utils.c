#include "philosophers.h"

// Thread-safe 'end_sim' value checker.
int	get_end_sim(t_table *table)
{
	int	value;

	pthread_mutex_lock(&table->stop_mutex);
	value = table->end_sim;
	pthread_mutex_unlock(&table->stop_mutex);
	return (value);
}

// Thread-safe 'end_sim' value updater.
void	set_end_sim(t_table *table, int value)
{
	pthread_mutex_lock(&table->stop_mutex);
	table->end_sim = value;
	pthread_mutex_unlock(&table->stop_mutex);
}

// Thread-safe 'last_meal' value checker for philo[i].
long	get_last_meal(t_philo *philo)
{
	long	value;

	pthread_mutex_lock(&philo->meal_mutex);
	value = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (value);
}

// Thread-safe 'last_meal' value updated for philo[i].
void	set_last_meal(t_philo *philo, long time)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = time;
	pthread_mutex_unlock(&philo->meal_mutex);
}

// Thread-safe 'meals_eaten' value checker for philo[i].
int	get_meals_eaten(t_philo *philo)
{
	int	value;

	pthread_mutex_lock(&philo->meal_mutex);
	value = philo->meals_eaten;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (value);
}
