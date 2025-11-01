#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

# define SUCCESS 0
# define FAILURE 1

# define FALSE 0
# define TRUE 1

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
	int				meals_eaten;
	long			last_meal;
	t_table			*table;
	pthread_t		thread;
}	t_philo;

typedef struct s_table
{
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_meals;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	long			start_ms;
	int				end_sim;
	pthread_mutex_t	stop_mutex;
}	t_table;

// main.c
int	parse_input(int argc, char *argv[], t_table *table);
int	create_forks(t_table *table);
int	create_philos(t_table *table);
int	init_stop_mutex_and_end_flag(t_table *table);
int	start_threads(t_table *table);
int	join_threads(t_table *table);

// utils.c
int	pos_atoi(const char *s);
int	ft_strlen(const char *s);

// cleanup.c
int	exit_error(char *msg, t_table *table);
int	destroy_forks(t_table *table);
int free_philos(t_table *table);

// timing.c
long	fetch_time_ms(void);
long	time_since_start_ms(long start_ms);

// routine.c
void	*philo_routine(void *philo_data);
void	sync_start(t_philo *philo);
void	single_philo_case(t_philo *philo);
void	think(t_philo *philo);
void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	drop_forks(t_philo *philo);
void	philo_sleep(t_philo *philo);

#endif