#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <pthread.h>

# define SUCCESS 0
# define FAILURE 1

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
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
}	t_table;

// main.c
int	parse_input(int argc, char *argv[], t_table *table);
int	create_forks(t_table *table);
int	create_philos(t_table *table);
int	start_threads(t_table *table);
void	*philo_routine(void *arg);

// utils.c
int	pos_atoi(const char *s);
int	ft_strlen(const char *s);
int	ft_isdigit(int c);

// cleanup.c
int	exit_error(char *msg, t_table *table);
int	destroy_forks(t_table *table);
int free_philos(t_table *table);
 
#endif