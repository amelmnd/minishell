#include "minishell.h"

int	msh_random_0_99(t_msh *msh)
{
	int	usec;

	usec = 0;
	gettimeofday(msh->timestamp, NULL);
	usec = msh->timestamp->tv_usec;
	return (usec%100);
}

int	msh_random_0_127(t_msh *msh)
{
	int	usec;

	usec = 0;
	gettimeofday(msh->timestamp, NULL);
	usec = msh->timestamp->tv_usec;
	return (usec%256);
}