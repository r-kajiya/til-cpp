#include "stopwatch.h"


int main ()
{
	Stopwatch stopwatch {};

	stopwatch.Show ();

	for ( int i = 0; i < 100000000; i++)
	{
		i++;
	}

	stopwatch.Show ();

	for ( int i = 0; i < 100000000; i++ )
	{
		i++;
	}

	stopwatch.Stop ();

	getchar ();

	return 0;
}

