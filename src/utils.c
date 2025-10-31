#include "philosophers.h"

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