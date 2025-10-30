#include "philosophers.h"

int	exit_error(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (*s)
	{
		len++;
		s++;
	}
	return (len);
}

int	ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	else
		return (0);
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
			exit_error("ERROR: Negative values are invalid.");
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i] - '0');
		if (res > INT_MAX)
			exit_error("ERROR: Input too large.");
		i++;
	}
	if (s[i] != '\0' || res <= 0)
		exit_error("ERROR: Non-numeric or empty input.");
	return ((int)res);
}