#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

int	parse_input(int argc, char *argv[], int args[5]);
int	exit_error(char *msg);
int	ft_strlen(const char *s);
int	pos_atoi(const char *s);
int	ft_isdigit(int c);

#endif