#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_table
{
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_meals;
	pthread_mutex_t	*forks;
}	t_table;

// main.c
int	parse_input(int argc, char *argv[], t_table *table);
int	create_forks(t_table *table);

// utils.c
int	pos_atoi(const char *s);
int	exit_error(char *msg);
int	ft_strlen(const char *s);
int	ft_isdigit(int c);

#endif