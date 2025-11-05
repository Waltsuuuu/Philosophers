#include "philosophers.h"

// Initializes the stop mutex and sets the simulation stop flag to FALSE.
// On mutex_init() failure, cleanup and exit.
int	init_stop_mutex_and_end_flag(t_table *table)
{
	if (pthread_mutex_init(&table->stop_mutex, NULL) != SUCCESS)
		return (exit_error("ERROR: mutex_init() failure.", NULL));
	table->end_sim = FALSE;
	return (SUCCESS);
}

int	init_print_mutex(t_table *table)
{
	if (pthread_mutex_init(&table->print_mutex, NULL) != SUCCESS)
		return (exit_error("ERROR: mutex_init() failure.", table));
	return (SUCCESS);
}

// Converts a numeric string to an integer.
// Error and exit if input is:
//  - non-numeric.
//	- negative.
//	- greater than INT_MAX.
//	- empty or 0.
int	pos_atoi(const char *s)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == ' ')
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			exit_error("ERROR: Negative values are invalid.", NULL);
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i] - '0');
		if (res > INT_MAX)
			exit_error("ERROR: Input too large.", NULL);
		i++;
	}
	if (s[i] != '\0' || res <= 0)
		exit_error("ERROR: Non-numeric or empty input.", NULL);
	return ((int)res);
}

// Thread-safe 'meals_eaten' value incrementer for philo[i].
void	increment_meals_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->meal_mutex);
}

// Thread-safe printf.
// Denies printing if 'end_sim' is set to true,
// to prevent prints after a death has occured.
void	safe_print(t_philo *philo, char *text)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	if (get_end_sim(philo->table) == FALSE)
		printf("%ld %d %s\n", sim_runtime_ms(philo->table->start_ms),
			philo->id, text);
	pthread_mutex_unlock(&philo->table->print_mutex);
}
